#include "searchServer.h"

searchServer::searchServer(QWidget *parent)
: QMainWindow(parent) 
{
    // first get the screen size -> and then get the window size
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();
    width = screenGeometry.width() / 2 ;
    height = screenGeometry.height() / 2;
    
    // load the image, image from base64-enconded
    QByteArray byteArray = QByteArray::fromBase64(pop_close);
    QPixmap backgroundImage;
    backgroundImage.loadFromData(byteArray);

    // this is for displaying the image
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, width, height); // Set geometry to cover the entire window
    backgroundLabel->setPixmap(backgroundImage.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setAlignment(Qt::AlignCenter);

    // image in opacity
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(0.6); 
    backgroundLabel->setGraphicsEffect(opacityEffect);
   
    // window title
    setWindowTitle("ASK POPCAT");
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    resize(width, height);     

    // showing the instructions in the window
    QLabel *instructionLabel = new QLabel("SEARCH STH USEFUL, U CUNT", this);
    instructionLabel->setAlignment(Qt::AlignCenter); 
    QFont font = instructionLabel->font();
    font.setPointSize(25); 
    instructionLabel->setFont(font);

    // create search line edit widget
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setFixedSize(width/2, height/10);
    font = searchLineEdit->font();
    font.setPointSize(20);
    searchLineEdit->setFont(font);

    // layout of the widget
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(searchLineEdit);
    mainLayout->addStretch();
    mainLayout->setAlignment(Qt::AlignCenter);

    // wrap the layout with a central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Create a timer to trigger the search operation after a delay
    searchTimer = new QTimer(this);
    searchTimer->setInterval(10); // 10 ms delay
    searchTimer->setSingleShot(true); 

    // single-shot timer - fire once and stop
    connect(searchLineEdit, &QLineEdit::textChanged, this, &searchServer::searchTextChanged);
    // textChanged function is shot by QLineEdit
    // searchTextChanged is called a slot (function)
    connect(searchTimer, &QTimer::timeout, this, &searchServer::performSearch);

    // create resize timer
    resizeTimer = new QTimer(this);

    // Set the interval for the timer (in milliseconds)
    resizeTimer->setInterval(1);
    connect(resizeTimer, &QTimer::timeout, this, &searchServer::setWindowSize);
    resizeTimer->start();
}

searchServer::~searchServer() {
}

void searchServer::searchTextChanged(const QString &text) {
    // Reset the timer to wait for another 1 second before triggering the search
    searchTimer->start();

    if (text.isEmpty()) {
        resetWidget(true);
        search_or_not = false;
    }
}

void searchServer::performSearch() {

    int itemCount = mainLayout->count();
    search_or_not = false;

    // retrieve the search query from the line edit
    QString searchQuery = searchLineEdit->text();
    
    std::vector<std::string> search_result = searchInstance(searchQuery.toStdString());

    QString searchResultDisplay;

    bool search_flag = true;
    if(!search_result.empty())
    {
        for (auto what : search_result)
            if (what == "KEEP SEARCHING!")
                search_flag = false;            
            
        if(search_flag)    
            search_or_not = true;
        
        searchResultDisplay = vectorString2QString(search_result);
    } 
    else
    {
        searchResultDisplay = searchQuery;
        search_flag = false;
    }

    if (search_flag)
        setImage(pop_open);
    else
        setImage(pop_close);

    // if(search_start)
        resetWidget(false);
    
    
    itemCount = mainLayout->count();
    
    QLabel *resultLabel = new QLabel(this);

    resultLabel->setAlignment(Qt::AlignCenter); // Align text to the center

    QFont font = resultLabel->font();
    font.setPointSize(16); // Set font size to 20 (adjust as needed)
    resultLabel->setFont(font);

    // add resultLabel to main layout
    resultLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);    
    resultLabel->setText(searchResultDisplay);
    mainLayout->addWidget(resultLabel);
    itemCount = mainLayout->count();

    search_start = true;
}

void searchServer::resetWidget(bool resetSearchFlag) 
{
    int itemCount = mainLayout->count();

    // If there are items in the layout
    if (itemCount > 3) {  
        // Ensure we leave the instruction and searchLineEdit
        QLayoutItem *lastItem = mainLayout->takeAt(itemCount - 1);
        
        // get the widget from the layout item
        QWidget *widget = lastItem->widget();
        
        // if the widget exists, remove and delete it
        if (widget) {
            mainLayout->removeWidget(widget);
            delete widget;
        }

        // delete the layout item
        delete lastItem;
    }

    // reset search flag if needed
    if (resetSearchFlag) {
        search_start = false;
    }
}

void searchServer::setWindowSize()
{
    if(!search_or_not)
    {
        resize(width, height);
        mainLayout->update();
        setImage(pop_close);

        return;
    }

    int width_now = QMainWindow().width();
    int height_now = QMainWindow().width();

    if (width_now != width || height_now != height)
    {
        resize(width, height);
        mainLayout->update();
    }

}

void searchServer::setImage(const char* image)
{
    // load the image, image from base64-enconded
    QByteArray byteArray = QByteArray::fromBase64(image);
    QPixmap backgroundImage;
    backgroundImage.loadFromData(byteArray);

    // this is for displaying the image
    backgroundLabel->setPixmap(backgroundImage.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    backgroundLabel->setAlignment(Qt::AlignCenter);
}

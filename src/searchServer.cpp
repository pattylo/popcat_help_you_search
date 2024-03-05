#include "searchServer.h"

searchServer::searchServer(QWidget *parent)
: QMainWindow(parent) 
{
    // Get the primary screen
    QScreen *primaryScreen = QGuiApplication::primaryScreen();

    // Get the screen geometry
    QRect screenGeometry = primaryScreen->geometry();

    // Calculate the size for the GUI window (one-quarter of the screen size)
    int width = screenGeometry.width() / 2 * 1.4;
    int height = screenGeometry.height() / 2 * 1.4;
    
    // Load the image
    QByteArray byteArray = QByteArray::fromBase64(popcatImageData);
    QPixmap backgroundImage;
    backgroundImage.loadFromData(byteArray);

    // Create a QLabel for the background image
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, width, height); // Set geometry to cover the entire window

    // Set the background image using a pixmap
    backgroundLabel->setPixmap(backgroundImage.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Center-align the background image within the window
    backgroundLabel->setAlignment(Qt::AlignCenter);

    // Create a QGraphicsOpacityEffect to adjust the opacity of the image
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(0.6); // Set opacity value (ranges from 0.0 to 1.0, where 0.0 is fully transparent and 1.0 is fully opaque)

    // Apply the QGraphicsOpacityEffect to the backgroundLabel
    backgroundLabel->setGraphicsEffect(opacityEffect);
   

    setWindowTitle("PATTY'S INDEX SEARCH!");
    resize(width, height);
    // setFixedSize(_
    

    QLabel *instructionLabel = new QLabel("SEARCH FOR USEFUL COMMANDLINE!", this);
    instructionLabel->setAlignment(Qt::AlignCenter); // Center-align the text

    QFont font = instructionLabel->font();
    font.setPointSize(25); // Set font size to 20 (adjust as needed)
    instructionLabel->setFont(font);


    // Create search line edit
    searchLineEdit = new QLineEdit(this);

    // Create layout and add widget
    mainLayout = new QVBoxLayout;

    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(searchLineEdit);

    mainLayout->addStretch();

    // Create a central widget and set the layout
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Create a timer to trigger the search operation after a delay
    searchTimer = new QTimer(this);
    searchTimer->setInterval(10); // 1 second delay
    searchTimer->setSingleShot(true); // Single-shot timer
    connect(searchLineEdit, &QLineEdit::textChanged, this, &searchServer::searchTextChanged);
    connect(searchTimer, &QTimer::timeout, this, &searchServer::performSearch);
}

searchServer::~searchServer() {
}

void searchServer::searchTextChanged(const QString &text) {
    // Reset the timer to wait for another 1 second before triggering the search
    searchTimer->start();
}

void searchServer::performSearch() {
    // Retrieve the search query from the line edit
    QString searchQuery = searchLineEdit->text();
    
    std::vector<std::string> search_result = searchInstance(searchQuery.toStdString());

    QString searchResultDisplay;
    if(!search_result.empty())
    {
        searchResultDisplay = vectorString2QString(search_result);
    } 
    else
    {
        searchResultDisplay = searchQuery;
    }

    if(search_start)
    {
        int itemCount = mainLayout->count();

        // If there are items in the layout
        if (itemCount > 0) {
            // Get the last added item
            QLayoutItem *lastItem = mainLayout->takeAt(itemCount - 1);
            
            // Get the widget from the layout item
            QWidget *widget = lastItem->widget();
            
            // If the widget exists
            if (widget) {
                // Remove the widget from the layout
                mainLayout->removeWidget(widget);
                
                // Delete the widget
                delete widget;
            }
            
            // Delete the layout item
            delete lastItem;
        }

    }
    
    
    QLabel *resultLabel = new QLabel(this);

    resultLabel->setAlignment(Qt::AlignCenter); // Align text to the center
    // resultLabel->setAlignment(Qt::AlignVCenter); // Align text to the center

    QFont font = resultLabel->font();
    font.setPointSize(16); // Set font size to 20 (adjust as needed)
    resultLabel->setFont(font);

    // Add the resultLabel to the main layout
    mainLayout->addWidget(resultLabel);

    // Whenever you have a search result to display:

    resultLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    
    resultLabel->setText(searchResultDisplay);

    // resultLabel->clear();

    search_start = true;


}

#include "searchServer.h"

std::vector<std::string> searchServer::splitString(const std::string& input) {
    // Regular expression to match words separated by space, semicolon, or slash
    std::regex re("[\\s;/]+");
    // Iterator to loop through each word
    std::sregex_token_iterator it(input.begin(), input.end(), re, -1);
    // End iterator
    std::sregex_token_iterator end;
    // Vector to store the split words
    std::vector<std::string> words;
    // Loop through each word and add it to the vector
    for (; it != end; ++it) {
        words.push_back(it->str());
    }
    return words;
}

bool searchServer::searchVectorString(
    const std::string& keyword, 
    const std::vector<std::string> to_be_searched
)
{
    for(int i = 0; i < to_be_searched.size(); i++)
    {
        if(keyword == to_be_searched[i])
            return true;
    }
        
    return false;
}


std::tuple<bool, std::vector<std::string>> searchServer::searchSubcategoryCommands(
    std::vector<std::string> query_keyword,
    int category_index
)
{
    bool search_result;

    for (const auto keyword : query_keyword)
    {
        for (int i = 0; i < database[category_index].subcate.size(); i++)
        {
            if(searchVectorString(
                    keyword, 
                    database[category_index].subcate[i].keywords
                )
            )
            {
                return {true, database[category_index].subcate[i].commands};
            }
                
        }
    }

    std::vector<std::string> nothing;
    return {false, nothing};
}

std::tuple<bool, int> searchServer::searchCategory(const std::string& keyword)
{
    std::tuple<bool, int> result;

    for(int i = 0; i < database.size(); i++)
    {
        if(searchVectorString(keyword, database[i].keywords))
        {
            return {true, i};
        }
    }

    return {false, -1};
}

std::vector<std::string> searchServer::searchInstance(const std::string& userInput) 
{
    std::vector<std::string> query_keywords = splitString(userInput);
    std::tuple<bool, int> category_result;

    for(const auto what : query_keywords)
    {
        category_result = searchCategory(what);

        if(std::get<0>(category_result))
            break;
    }

    if(std::get<1>(category_result) < 0)
    {
        query_keywords.emplace_back("NULL");
        return query_keywords;
    }

    // std::cout<<database[std::get<1>(category_result)].name<<std::endl<<std::endl;

    std::tuple<bool,std::vector<std::string>> display_results = searchSubcategoryCommands(
        query_keywords, 
        std::get<1>(category_result)
    );

    // for(const auto what : std::get<1>(display_results))
    // {
    //     std::cout<<what<<std::endl;
    // }

    return std::get<1>(display_results);
}

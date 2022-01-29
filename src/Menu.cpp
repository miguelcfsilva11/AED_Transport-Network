#include "Menu.h"


Menu::Menu()
{
    this->net = TransportNetwork();
}

void Menu::execute()
{
    char key;
    string file_stops = "../dataset/stops.csv";
    string file_lines = "../dataset/lines.csv";

    net.readStops(file_stops);
    net.readLines(file_lines, CW.hiddenLines);


    float cost = 0;
    float min_cost = INT_MAX/2;

    pair<list<int>, float> shortestPathCost;

    Graph* g = net.getGraph();

    int stop1_index = g->getStopIndex(CW.startStop);
    int stop2_index = g->getStopIndex(CW.endStop);

    if (CW.howToChooseRoute == 0)
    {
        shortestPathCost = g->dijkstraDistance(stop1_index, stop2_index);
    
    }

    else if (CW.howToChooseRoute == 1)
    {
        for (auto line: g->getStops()[stop1_index].lines)
        {
            pair<list<int>, float> pathCost = g->minLinesDistance(stop1_index,stop2_index, line);
            
            cost = pathCost.second;
            if (cost < min_cost)
                min_cost = cost;
                shortestPathCost = pathCost;
        }

    }

    else
        shortestPathCost = g->minZonesDistance(stop1_index, stop2_index);

    for (int i = 0; i < 50; i++)
    {
        cout << '\n';
    }

    cout << "According to your preferences, the shortest route  that takes you from / to:\n -> "
         << g->getStops()[stop1_index].name << "\n -> " << g->getStops()[stop2_index].name
         << "\n is the following:" << endl;

    list<int> chosenPath = shortestPathCost.first;
    float chosenCost = shortestPathCost.second;

    auto it = chosenPath.begin();

    while (it != chosenPath.end())
    {
        cout << g->getStops().at(*it).code << ": " << g->getStops().at(*it).name << endl;
        it++;

        if (it != chosenPath.end())
            cout << "|" << endl;
    }

    cout << "Continue: ";
    cin >> key;

}

void Menu::cleanScreen()
{
    for (int i = 0; i < 50; i++)
    {
        cout << '\n';
    }
}


int Menu::printMenu()
{

    int decision = -1;

    while (decision != 1 & decision != 2)
    {
    
        cleanScreen();

        std::cout << "   Menu   \n" << std::endl;
        std::cout << "0 - Instruções" << std::endl;
        std::cout << "1 - Escolher percurso " << std::endl;
        std::cout << "2 - Quit" << std::endl;

        std::cin >> decision;
        
        if (decision == 0)
            showInfo();
    }

    if (decision == 1)
    {
        chooseWay();
    }
    cout << decision << ": hey" << endl;
    return decision;

};


void Menu::showInfo()
{

    char key;

    cleanScreen();

    std::cout << "Continue: ";
    cin >> key;

};



void Menu::chooseWay()
{

    int decision;
    string code;
    char c;

    cleanScreen();

    std::cout<< "Como quer escolher a localização onde se encontra?" << std::endl;
    std::cout<< "0 - Estação" << std::endl;
    std::cout<< "1 - Latitude e longitude" << std::endl;

    std::cin>> decision;

    while (decision != 0 && decision != 1)
    {
        std::cin>> decision;
    }


    if(decision == 0)
    {
        std::cout<<"Qual o código da estação de onde vai partir?" << std::endl;
        std::cin >> CW.startStop;


    }
    else if (decision == 1)
    {
        std::cout<<"Qual a latitude/longitude de onde vai partir?" << std::endl;
        std::cin >> CW.startLat >> c >> CW.startLong;
    }


    cleanScreen();

    std::cout<< "Como quer escolher a localização para onde vai?" << std::endl;
    std::cout<< "0 - Estação" << std::endl;
    std::cout<< "1 - Latitude e longitude" << std::endl;

    std::cin>> decision;

    if(decision == 0)
    {
        std::cout<<"Qual o código da estação para onde vai?" << std::endl;
        std::cin >> CW.endStop;
    }
    else if (decision == 1)
    {
        std::cout<<"Qual a latitude/longitude do lugar para onde vai?" << std::endl;
        std::cin >> CW.endLat >> c >> CW.endLong;
    }

    cleanScreen();

    std::cout<< "Como prefere que o seu percurso seja escolhido?" << std::endl;
    std::cout << "0 - Trajeto mais curto" << std::endl;
    std::cout << "1 - Menor número de trocas de linha" << std::endl;
    std::cout << "2 - Mais barato (menos mudanças de zona)" << std::endl;

    std::cin >> CW.howToChooseRoute;

    while (CW.howToChooseRoute != 0 && CW.howToChooseRoute != 2 && CW.howToChooseRoute != 1)
        std::cin >> CW.howToChooseRoute;

    cleanScreen();

    std::cout<< "Está disposto a andar  a pé para trocar de transporte?" << std::endl;
    std::cout << "0 - Sim" << std::endl;
    std::cout << "1 - Não" << std::endl;

    std::cin >> decision;

    if (decision == 0) {
        CW.goOnFoot = true;
        std::cout << "Quantos metros está disposto a andar a pé?" << std::endl;
        std::cin >> CW.metresToWalk;
    }
    else if (decision == 1)
        CW.goOnFoot = false;


    cleanScreen();

    std::cout<< "Quer suprimir alguma linha? Por favor escreva o código da linha que desejar suprimir.\n (se não quiser suprimeir nenhuma loinha escreva o código 0000)" << std::endl;
    std::cin >> code;

    while(code != "0000")
    {
        CW.hiddenLines.insert(code);
        std::cin>>code;

    }


};
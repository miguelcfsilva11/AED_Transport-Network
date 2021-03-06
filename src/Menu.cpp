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
    net.readLines(file_lines, CW.hiddenLines, CW.nightTime);



    float cost = 0;
    float min_cost = INT_MAX/2;

    pair<list<int>, float> shortestPathCost;

    Graph* g = net.getGraph();
    if(CW.startStop == " "){
        g->addYourLocation(CW.startLat,CW.startLong,CW.metresToWalk);
        CW.startStop = "Your Location";
    }

    int stop1_index = g->getStopIndex(CW.startStop);
    int stop2_index = g->getStopIndex(CW.endStop);

    if (stop1_index == -1 || stop2_index == -1)
    {
        cout << "Error: there is no stop with such code, please try again!" << endl;
        if( stop2_index == -1){
            cout << "Missing Stop: "<< CW.endStop << endl;
        }
        if (stop1_index == -1) cout << "Missing Stop: " <<  CW.startStop << endl;
            
        cout << "\n -> Continue: ";
        cin >> key;
        return;

    }
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

    else if(CW.howToChooseRoute == 2)
        shortestPathCost = g->minZonesDistance(stop1_index, stop2_index);
    
    else shortestPathCost = g->BFS(stop1_index, stop2_index);

    for (int i = 0; i < 50; i++)
    {
        cout << '\n';
    }

    cout << "According to your preferences, the shortest route that takes you from / to:\n\n -> "
         << g->getStops()[stop1_index].name << "\n -> " << g->getStops()[stop2_index].name
         << "\n\n is the following:\n" << endl;

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

    cout << "\n -> Continue: ";
    cin >> key;

};

void Menu::cleanScreen()
{
    for (int i = 0; i < 50; i++)
    {
        cout << '\n';
    }
}


void Menu::printMST()
{
    cout << "ENtered function "<< endl;
    string zone, stopCode;
    char key;

    string file_stops = "../dataset/stops.csv";
    string file_lines = "../dataset/lines.csv";


    net.readStops(file_stops);
    net.readLines(file_lines, CW.hiddenLines, CW.nightTime);

    cleanScreen();

    std::cout<< "Qual o nome da zona que deseja percorrer?\n -> ";
    std::cin >> zone;

    std::cout<< "A partir de que paragem?\n -> ";
    std::cin >> stopCode;
    Graph* g = net.getGraph();

    if (g->getStopIndex(stopCode) == -1)
    {
        std::cout<< "Paragem inv??lida:\n -> ";
        std::cin >> key;
        return;
    }

    if(g->getStops().at(g->getStopIndex(stopCode)).zone != zone)
    {
        std::cout<< "A zona nao corresponde ?? paragem:\n -> ";
        std::cin >> key;
        return;
    }

    pair<list<int>, float> primPathCost = g->primDistance(g->getStopIndex(stopCode), zone);
    
    cleanScreen();

    cout << "According to your preferences, the shortest route to traverse the zone / from:\n\n -> "
        << zone << "\n -> " << g->getStops()[g->getStopIndex(stopCode)].name
        << "\n\n is the following:\n" << endl;

    list<int> chosenPath = primPathCost.first;
    float chosenCost = primPathCost.second;


    auto it = chosenPath.begin();

    while (it != chosenPath.end())
    {
        cout << g->getStops().at(*it).code << ": " << g->getStops().at(*it).name<< "\n";

        it++;

        if (it != chosenPath.end())
            cout << "|" << endl;
    }

    cout << "\n -> Exit:  ";
    cin >> key;

}

int Menu::printMenu()
{

    int decision = -1;

    while (decision != 1 & decision != 2 && decision != 3)
    {
    
        cleanScreen();

        std::cout << "   Menu   \n" << std::endl;
        std::cout << "0 - Instru????es" << std::endl;
        std::cout << "1 - Escolher percurso " << std::endl;
        std::cout << "2 - Escolher MST " << std::endl;
        std::cout << "3 - Quit" << std::endl;

        std::cin >> decision;
        
        if (decision == 0)
            showInfo();
    }

    if (decision == 1)
    {
        chooseWay();
    }
    if (decision == 2)
    {
        printMST();
    }

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

    std::cout<< "Como quer escolher a localiza????o onde se encontra?" << std::endl;
    std::cout<< "0 - Esta????o" << std::endl;
    std::cout<< "1 - Latitude e longitude\n -> ";

    std::cin>> decision;

    while (decision != 0 && decision != 1)
    {
        std::cin>> decision;
    }


    if(decision == 0)
    {
        std::cout<<"Qual o c??digo da esta????o de onde vai partir? \n -> ";
        std::cin >> CW.startStop;


    }
    else if (decision == 1)
    {
        std::cout<<"Qual a latitude/longitude de onde vai partir? \n";

        cout << "-> Latitude :  ";
        cin >> CW.startLat;
        cout << "-> Longitude : ";
        cin >> CW.startLong;
        // cout << "Latitude :  "<< CW.startLat << endl;
        // cout << "Longitude : "<< CW.startLong << endl;
    }


    cleanScreen();

    std::cout<< "Como quer escolher a localiza????o para onde vai?\n" << std::endl;
    std::cout<< "0 - Esta????o" << std::endl;
    std::cin>> decision;

    if(decision == 0)
    {
        std::cout<<"Qual o c??digo da esta????o para onde vai? \n -> ";
        std::cin >> CW.endStop;
    }

    cleanScreen();

    std::cout<< "Como prefere que o seu percurso seja escolhido?\n" << std::endl;
    std::cout << "0 - Trajeto mais curto" << std::endl;
    std::cout << "1 - Menor n??mero de trocas de linha" << std::endl;
    std::cout << "2 - Mais barato (menos mudan??as de zona)" << std::endl;
    std::cout << "3 - Menor n??mero de paragens \n -> ";

    std::cin >> CW.howToChooseRoute;

    while (CW.howToChooseRoute != 0 && CW.howToChooseRoute
                != 2 && CW.howToChooseRoute != 1 && CW.howToChooseRoute != 3) 
        std::cin >> CW.howToChooseRoute;

    cleanScreen();

    std::cout<< "Est?? disposto a andar a p?? para trocar de transporte?\n" << std::endl;
    std::cout << "0 - N??o" << std::endl;
    std::cout << "1 - Sim \n -> ";

    std::cin >> decision;

    if (decision == 1) {
        CW.goOnFoot = true;
        std::cout << "Quantos metros est?? disposto a andar a p??? \n -> ";
        std::cin >> CW.metresToWalk;
    }

    else if (decision == 0)
        CW.goOnFoot = false;
    
    std::cout<< "Ser?? uma viagem noturna? De madrugada?\n" << std::endl;
    std::cout << "0 - N??o" << std::endl;
    std::cout << "1 - Sim \n -> ";

    std::cin >> decision;

    if (decision == 0) CW.nightTime = false;
    else if (decision == 1) CW.nightTime = true;

    cleanScreen();

    std::cout<< "Quer suprimir alguma linha? Por favor escreva o c??digo da linha\n"
             << "que desejar suprimir." 
             << "(Se n??o quiser suprimeir nenhuma loinha escreva o c??digo '0000') \n -> ";
    std::cin >> code;

    while(code != "0000")
    {
        CW.hiddenLines.insert(code);
        std::cin>>code;

    }
};
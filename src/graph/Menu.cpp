
#include "Menu.h"


Menu::Menu()
{
    choosingWay CW;
    CW = printMenu();
}


choosingWay Menu::printMenu()
{

    choosingWay CW;
    int decision;

    std::cout << "   Menu   \n" << std::endl;
    std::cout << "0 - Instruções" << std::endl;
    std::cout << "1 - Escolher percurso " << std::endl;
    std::cout << "2 - Quit" << std::endl;

    std::cin >> decision;

    if (decision == 0)
        showInfo();

    else if (decision == 1)
    {
        CW = chooseWay();
    }

    return CW;

};


void Menu::showInfo()
{

    std::cout << "Blablabla" << std::endl;

};



choosingWay Menu::chooseWay()
{
    choosingWay CW;
    int decision;
    char c;
    string code;

    std::cout<< "Como quer escolher a localização onde se encontra?" << std::endl;
    std::cout<< "0 - Estação" << std::endl;
    std::cout<< "1 - Latitude e longitude" << std::endl;

    std::cin>> decision;

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


    std::cout<< "Como quer escolher a localização para onde vai?" << std::endl;
    std::cout<< "0 - Estação" << std::endl;
    std::cout<< "1 - Latitude e longitude" << std::endl;

    std::cin>> decision;

    if(decision == 0)
    {
        std::cout<<"Qual o código da estação para onde vai?" << std::endl;
        std::cin >> CW.endStop;
    }
    else if (decidion == 1)
    {
        std::cout<<"Qual a latitude/longitude do lugar para onde vai?" << std::endl;
        std::cin >> CW.endLat >> c >> CW.endLong;
    }


    std::cout<< "Como prefere que o seu percurso seja escolhido?" << std::endl;
    std::cout << "0 - Trajeto mais curto" << std::endl;
    std::cout << "1 - Menor número de trocas de linha" << std::endl;
    std::cout << "2 - Mais barato (menos mudanças de zona)" << std::endl;

    std::cin >> CW.howToChooseRoute;

    std::cout<< "Está disposto a andar  a pé para trocar de transporte?" << std::endl;
    std::cout << "0 - Sim" << std::endl;
    std::cout << "1 - Não" << std::endl;

    std::cin >> decision;

    if (decision == 0) {
        CW.goOnFoot = true;
        std::cout << "Quantos metros está disposto a andar a pé?" << std::endl;
        std::cin >> CW.metresToWalk
    }
    else if (decision == 1)
        CW.goOnFoot = false;



    std::cout<< "Quer suprimir alguma linha? Por favor escreva o código da linha que desejar suprimir.\n (se não quiser suprimeir nenhuma loinha escreva o código 0000)" << std::endl;
    std::cin >> code;

    while(code != 0000)
    {
        CW.hiddenLines.push_back(code);
        std::cin>>code;

    }



return CW;


};
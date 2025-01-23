//refactored game - fixing long methods code smell:
#include "headers/game.hpp"
#include "headers/compatible.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

//////////////* Default Constructor *////

Game::Game(){
    deck.initializeDeck();
}

//////////////* Deals dealer towards the end *////

bool Game::dealDealer(){
    if(dealer.getSum() < player.getSum()){
        while (dealer.getSum() < 17){
            dealer.addCard(deck.deal());
            if (checkWins()){
                return false;
            }
        }
        return true;
    } else {
        return !checkWins();
    }
}

//////////////* Checkers *////

char Game::compareSum(){
    if(player.getSum() > dealer.getSum()){
        printTop();
        std::cout << lightYellow << Print::you_win() << def << "\n    (Dealer has " << dealer.getSum() << ")\n";
        return 'p';
    } else if(dealer.getSum() > player.getSum()){
        printTop();
        std::cout << lightRed << Print::dealer_wins() << def << "\n    (" << dealer.getSum() << ")\n";
        return 'd';
    } else {
        printTop();
        std::cout << lightMagenta << Print::draw() << def;
        return 'n';
    }
}

bool Game::checkWins(){
    switch(checkEnd()){
        case 'f': return false;
        case 'd': player.incrementLoses(); return true;
        case 'p': player.incrementWins();
                  player.addCash(player.getBet() * 2);
                  return true;
    }
    return false;
}

char Game::checkEnd(){
    if(dealer.getSum() > 21 || player.getSum() > 21){
        printTop();
        std::cout << red << Print::bust() << def << "\n    [Dealer : " << dealer.getSum() << " | " << player.getName() << " : " << player.getSum() << "]\n";
        return dealer.getSum() > 21 ? 'p' : 'd';
    } else if(dealer.isBlackjack() || player.isBlackjack()) {
        printTop();
        std::cout << lightGreen << Print::blackjack() << def << "\n    [Dealer : " << dealer.getSum() << " | " << player.getName() << " : " << player.getSum() << "]\n";
        return dealer.isBlackjack() ? 'd' : 'p';
    }
    return 'f';
}

//////////////* Game Starters *////

bool Game::startBet(){
    if(player.getCash() > 0){
        while(true){
            printTop();
            std::cout << "Place your bet!\t\t $" << green << player.getBet() << def << "\n[W = Raise Bet | S = Decrease Bet | R = Done]\n";
            int c = toupper(getchar());
            switch(c){
                case 'W': if(player.getCash() >= 5){ player.setBet(5); } break;
                case 'S': if(player.getBet() >= 5){ player.setBet(-5); } break;
            }
            if(c == 'R') break;
        }
        return true;
    } else {
        return false;
    }
}

void Game::dealInitialCards(){
    player.addCard(deck.deal());
    dealer.addCard(deck.deal());
    player.addCard(deck.deal());
    dealer.addCard(deck.deal());
}

bool Game::checkImmediateWin(){
    return checkWins();
}

bool Game::processPlayerActions(){
    while(true){
        std::cout << lightYellow << "\n\nH : Hit | S : Stand\n" << def;
        int c = toupper(getchar());
        if(c == 'H'){
            player.addCard(deck.deal());
            printBody();
            if(checkWins()) return false;
        } else if(c == 'S'){
            break;
        }
    }
    return true;
}

bool Game::startGame(){
    dealInitialCards();
    printBody();
    if(checkImmediateWin()) return false;
    return processPlayerActions();
}

void Game::initializeGameState(){
    if(deck.getSize() < 36) deck.initializeDeck();
    player.clearCards();
    dealer.clearCards();
}

bool Game::handleBets(){
    return startBet();
}

void Game::finalizeRound(){
    std::cout << lightRed << Print::dealer_border() << def;
    dealer.printCards();
    std::cout << lightCyan << Print::player_border() << def;
    player.printCards();
    std::cout << yellow << "\nYour wins: " << player.getWins() << lightRed << "\nYour losses: " << player.getLoses() << def << "\n";
    if(s.check(player)){
        std::cout << lightYellow << "High Score!\n" << def;
    }
}

void Game::saveGamePrompt(){
    char saveChoice;
    std::cout << "\nSave game? [Y/N]: ";
    std::cin >> saveChoice;
    if(saveChoice == 'Y' || saveChoice == 'y'){
        saveGame();
    }
}

void Game::beginGame(){
    char cont;
    do{
        initializeGameState();
        if(!handleBets()){
            std::cout << lightRed << "\nBankrupt! Game over.\n" << def;
            break;
        }
        if(startGame() && dealDealer()){
            switch(compareSum()){
                case 'p': player.incrementWins(); 
                          player.addCash(player.getBet() * 2); break;
                case 'd': player.incrementLoses(); break;
                case 'n': player.addCash(player.getBet()); break;
            }
        }
        finalizeRound();
        std::cout << "\nContinue playing? [Y/N]: ";
        std::cin >> cont;
    } while(cont != 'N' && cont != 'n');
    saveGamePrompt();
}

//////////////* Menu System *////

void Game::beginMenu(bool rep, std::string message){
    clearscr();
    std::cout << yellow << Print::title_blackjack() << def << "\n";
    std::cout << Print::begin_menu() << "\n";
    if(rep){
        std::cout << red << message << def << "\n";
    }
    char c;
    std::cout << "Input: ";
    std::cin >> c;
    switch(c){
        case '1': handleStartNewGame(); break;
        case '2': handleLoadGame(); break;
        case '3': handleViewStatistics(); break;
        case '4': handleViewInstructions(); break;
        case '5': exit(0);
        default: beginMenu(true, "Invalid input.");
    }
}

void Game::handleStartNewGame(){
    char nm[100];
    std::cout << "Enter player name: ";
    std::cin >> nm;
    player.setName(nm);
    beginGame();
}

void Game::handleLoadGame(){
    loadGame();
    beginGame();
}

void Game::handleViewStatistics(){
    printStatistics();
    beginMenu(false, "");
}

void Game::handleViewInstructions(){
    printInstructions();
    beginMenu(false, "");
}

//////////////* File Handling *////

std::string Game::promptForFilename(){
    std::string filename;
    do{
        std::cout << "Enter filename: ";
        std::cin >> filename;
        std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
    } while(filename == "statistics");
    return filename;
}

bool Game::validateFileExistence(const std::string& path){
    std::fstream f(path, std::ios::in | std::ios::binary);
    if(!f.fail()){
        char choice;
        std::cout << red << "File already exists." << def << " Do you want to overwrite it? [Y/N]: ";
        std::cin >> choice;
        return (choice == 'N' || choice == 'n');
    }
    return false;
}

void Game::writeBinaryData(const std::string& path){
    std::fstream f(path, std::ios::out | std::ios::binary);
    std::string sName = player.getName();
    int sCash = player.getCash();
    int sWins = player.getWins();
    int sLoses = player.getLoses();
    int nameSize = sName.size();
    f.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    f.write(sName.c_str(), sName.size());
    f.write(reinterpret_cast<char*>(&sCash), sizeof(sCash));
    f.write(reinterpret_cast<char*>(&sWins), sizeof(sWins));
    f.write(reinterpret_cast<char*>(&sLoses), sizeof(sLoses));
    f.close();
}

void Game::saveGame(){
    std::string filename = promptForFilename();
    std::string path = "data/" + filename + ".bin";
    if(validateFileExistence(path)) return;
    writeBinaryData(path);
}

void Game::loadGame(){
    std::fstream f1;
    std::string filename = promptForFilename();
    std::string path = "data/" + filename + ".bin";
    f1.open(path, std::ios::in | std::ios::binary);
    if(!f1.fail()){
        std::string sName;
        int sCash, sWins, sLoses, nameSize;
        f1.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        sName.resize(nameSize);
        f1.read(&sName[0], sName.size());
        f1.read(reinterpret_cast<char*>(&sCash), sizeof(sCash));
        f1.read(reinterpret_cast<char*>(&sWins), sizeof(sWins));
        f1.read(reinterpret_cast<char*>(&sLoses), sizeof(sLoses));
        f1.close();
        player.setName(sName);
        player.addCash(sCash - player.getCash());
        while(player.getWins() != sWins){ player.incrementWins(); }
        while(player.getLoses() != sLoses){ player.incrementLoses(); }
    } else {
        beginMenu(true, "File does not exist.");
    }
}

//////////////* Printing Functions *////

void Game::printStatistics(){
    clearscr();
    std::cout << yellow << Print::title_blackjack() << def << "\n";
    std::cout << "\n" << lightGreen << Print::statistics() << def << "\n";
    s.print();
    std::cout << "\n\n\t(Press any key to continue)\n";
    getchar();
}

void Game::printInstructions(){
    clearscr();
    std::cout << yellow << Print::title_blackjack() << def << "\n";
    std::cout << "\n" << lightGreen << Print::instructions() << def << "\n";
    getchar();
}

void Game::printTop(){
    clearscr();
    std::cout << yellow << Print::title_blackjack() << def << "\n";
    std::cout << lightRed << "\t\tCards: " << deck.getSize() << lightGreen << " \tCash: " << player.getCash() 
              << lightMagenta << " \tBet: " << player.getBet() << lightBlue << " \tName: " << player.getName() << def << "\n\n\n";
}

void Game::printBody(){
    printTop();
    std::cout << lightRed << Print::dealer_border() << def;
    dealer.printFirstCard();
    std::cout << lightCyan << Print::player_border() << def;
    player.printCards();
    std::cout << lightGreen << "\nSum: " << lightRed << player.getSum() << def << "\n";
}
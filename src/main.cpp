#include <iostream>
#include "Menu.h"
#include "Data.h"
#include "Filereader.h"

int main() {
    Data* data = new Data();
    auto* filereader = new Filereader(data);
    filereader->read();
    Menu menu = Menu(data);
    return 0;
}

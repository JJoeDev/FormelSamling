#include "application.h"

int main(void){
    App& app = App::GetInstance();

    if(!app.Init("FOSS Formel samling")){
        return -1;
    }

    app.Run();

    return 0;
}
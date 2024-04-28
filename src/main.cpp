#include "application.h"

int main(void){
    App& app = App::GetInstance();

    if(!app.Init(1024, 770, "FOSS Formel samling")){
        return -1;
    }

    app.Run();

    return 0;
}
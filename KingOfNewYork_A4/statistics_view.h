//  Created by Jeremy Gaudet on 2018-10-27.
//  ID: #40045224
//  COMP_345_Section_N


#ifndef statistics_view_h
#define statistics_view_h

#include "engine.h"
#include "observer.h"

class StatisticsView : public Observer {
public:
    StatisticsView();
    ~StatisticsView() override;
    StatisticsView(Engine* game);
    void update() override;
    void update(Player* p) override;
    void display();
    std::string get_players_borough(std::string location);
    
private:
    Engine* _engine;
    
};


#endif /* statistics_view_h */

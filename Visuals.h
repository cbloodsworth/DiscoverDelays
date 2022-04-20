#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <queue>
#include <random>

/* ABANDON ALL HOPE, YE WHO ENTER */

using namespace std;

struct TM {
    map<string, sf::Texture> textures;

    void Load(string fileName) {
        string loc = "Images/";
        loc += fileName + ".png";

        textures[fileName].loadFromFile(loc);
    }
    sf::Texture& GetTexture(string t) {
        if (textures.find(t) == textures.end()) { Load(t); }

        return textures[t];
    }
};

static int screen_num = 0;

void monthSwap(string& n) {
    if (n[n.length() - 1] == '0') {
        n.erase(n.length() - 1);
        n = n + '1';
    }
    else if (n[n.length() - 1] == '1') {
        n.erase(n.length() - 1);
        n = n + '0';
    }
}

class DD_Program {
    sf::Sprite visualspr; // this sprite is for use on non-clickable objects
    sf::Sprite clkspr1;   // this sprite is for clickable objects
    TM ddtm;
    sf::Text data;
    sf::Font font;

    DataSet& ds;

    //helper map
    map<int, string> months = { {0, "but-m-jan-1"},
                                {1, "but-m-feb-1"},
                                {2, "but-m-mar-1"},
                                {3, "but-m-apr-1"},
                                {4, "but-m-may-1"},
                                {5, "but-m-jun-1"},
                                {6, "but-m-jul-1"},
                                {7, "but-m-aug-1"},
                                {8, "but-m-sep-1"},
                                {9, "but-m-oct-1"},
                                {10, "but-m-nov-1"},
                                {11, "but-m-dec-1"},
    };
    map<int, string> month_names = { {0, "January"},
                                     {1, "February"},
                                     {2, "March"},
                                     {3, "April"},
                                     {4, "May"},
                                     {5, "June"},
                                     {6, "July"},
                                     {7, "August"},
                                     {8, "September"},
                                     {9, "October"},
                                     {10, "November"},
                                     {11, "December"},
    };
    

    struct Button {
        TM tm;
        int xpos, ypos;
        bool clickable;
        sf::Texture tex;
        string name;
        sf::Vector2i size;
        sf::Vector2i pos;

        void click();

        Button() {}
        Button(string _tex, int _xpos, int _ypos) : tex(tm.GetTexture(_tex)) { 
            size.x = tex.getSize().x; 
            size.y = tex.getSize().y;
            pos.x = _xpos;
            pos.y = _ypos;
            name = _tex;
            clickable = false;
        }
        Button(string _tex, int _xpos, int _ypos, bool _clickable) : tex(tm.GetTexture(_tex)) {
            size.x = tex.getSize().x;
            size.y = tex.getSize().y;
            pos.x = _xpos;
            pos.y = _ypos;
            name = _tex;
            clickable = _clickable;
        }
    };

    vector<Button*> activeButtons;
    bool activeMonths[12];

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1024, 768), "DiscoverDelays");



public:
    // Create any buttons you want here, and...
    Button del_by_day;
    Button del_by_month;
    Button var_stats;

    Button jan; Button feb; Button mar; Button apr; Button may; Button jun;
    Button jul; Button aug; Button sep; Button oct; Button nov; Button dec;

    Button back;

    Button welc_banner;
    Button gdata;
    Button gbackground;
    
    
    //...initialize them here. String is the filename, then xpos and ypos. put true if you want them to be clickable, false if not.
    DD_Program(DataSet& d) : ds(d),
        del_by_day("but-dbd", 150, 350, true),
        del_by_month("but-dbm", 618, 350, true),
        var_stats("but-varstts", 384, 550, true),
        welc_banner("misc-welcbanner", 0, 50),
        jan("but-m-jan-0", 36, 36, true),
        feb("but-m-feb-0", 36, 72 + 10, true),
        mar("but-m-mar-0", 36, 108 + 20, true),
        apr("but-m-apr-0", 36, 144 + 30, true),
        may("but-m-may-0", 36, 180 + 40, true),
        jun("but-m-jun-0", 36, 216 + 50, true),
        jul("but-m-jul-0", 36, 252 + 60, true),
        aug("but-m-aug-0", 36, 288 + 70, true),
        sep("but-m-sep-0", 36, 324 + 80, true),
        oct("but-m-oct-0", 36, 360 + 90, true),
        nov("but-m-nov-0", 36, 396 + 100, true),
        dec("but-m-dec-0", 36, 432 + 110, true),
        back("but-back", 36, 700, true),
        gdata("misc-graphdata", 0, 0),
        gbackground("misc-graphbg", 175, 82) {}
        
    
    //pass in a month to flip in the array and it will flip it
    void updateActiveMonths() {
        int i = 0;
        for (auto& b : activeButtons) {
            if (b->name.length() > 4 && b->name[4] == 'm' && b->name[5] == '-') {
                if (b->name[b->name.length() - 1] == '1') {
                    activeMonths[i++] = true;
                } 
                else
                    activeMonths[i++] = false;
            }
        }
    }

    void turnOffButtons() {
        for (auto& b : activeButtons) {
            if (b->name.length() > 4 && b->name[4] == 'm' && b->name[5] == '-') {
                if (b->name[b->name.length() - 1] == '1') {
                    monthSwap(b->name);
                    b->tex = b->tm.GetTexture(b->name);
                }
            }
        }
    }

    void exclusiveButtons(Button m) {
        for (auto& b : activeButtons) {
            if (b->pos != m.pos && b->name.length()>4 && b->name[4] == 'm' && b->name[5] == '-') {
                if (b->name[b->name.length() - 1] == '1') {
                    monthSwap(b->name);
                    b->tex = b->tm.GetTexture(b->name);
                }
            }
        }
    }

	void openProgram() {    
        font.loadFromFile("Fonts/Centaur.ttf");
        data.setFont(font);
        data.setOutlineColor(sf::Color(0,0,0, 255));
        data.setOutlineThickness(1.5);
        while (window->isOpen())
        {  
            sf::Event event;
            // sets background to grey
            window->clear(sf::Color(200, 200, 200, 255));

            switch (screen_num) {
            case 0: // case 0 indicates title screen
                displayTitleScreen(); break;
            case 1: // case 1 indicates delays by day
                displayDelaysByDay(); break;  
            case 2: // case 2 indicates delays by month
                displayDelaysByMonth(); break;
            case 3: // case 3 indicates various stats
                displayVariousStats(); break;
            }
            
            // event loop
            while (window->pollEvent(event))
            {
                switch (event.type) {
                case (sf::Event::MouseButtonPressed):
                {
                    for (auto& b : activeButtons) {
                        // If the rectangle formed from b's sprite contains the mouse
                        if (sf::Rect<int>(b->pos, b->size).contains(sf::Mouse::getPosition(*window))) {
                            if (not b->clickable)
                                continue;
                            b->click();
                            if (screen_num == 0)
                                turnOffButtons();
                            else if (screen_num == 1)
                                exclusiveButtons(*b);

                            updateActiveMonths();
                        }
                    }
                } 
                break;

                case (sf::Event::Closed): 
                {
                    window->close();
                } 
                break;

                }

                
            }

            displayButtons();

            if (screen_num == 2)
                displayDBMGraph();
            
            window->display();
            
        }
	}

    // This will display all buttons in the vector and then clear it.
    void displayButtons() {
        while (not activeButtons.empty()) {
            Button* b = activeButtons.back();
            clkspr1.setTexture(b->tex, true);
            clkspr1.setPosition(b->pos.x, b->pos.y);
            window->draw(clkspr1);
            activeButtons.pop_back();
        }
    }

    // Push any buttons you want to appear on the title screen
    void displayTitleScreen() {
        activeButtons.push_back(&del_by_day);
        activeButtons.push_back(&del_by_month);
        activeButtons.push_back(&var_stats);
        activeButtons.push_back(&welc_banner);

        /* insert more buttons here if needed ?*/

        // This is to keep track of what screen we are on.
        screen_num = 0;
    }

    // Push any buttons you want to appear on the delays by day page
    void displayDelaysByDay() {
        activeButtons.push_back(&jan);
        activeButtons.push_back(&feb);
        activeButtons.push_back(&mar);
        activeButtons.push_back(&apr);
        activeButtons.push_back(&may);
        activeButtons.push_back(&jun);
        activeButtons.push_back(&jul);
        activeButtons.push_back(&aug);
        activeButtons.push_back(&sep);
        activeButtons.push_back(&oct);
        activeButtons.push_back(&nov);
        activeButtons.push_back(&dec);
        activeButtons.push_back(&back);

        screen_num = 1;
    }

    void displayDelaysByMonth() {
        activeButtons.push_back(&jan);
        activeButtons.push_back(&feb);
        activeButtons.push_back(&mar);
        activeButtons.push_back(&apr);
        activeButtons.push_back(&may);
        activeButtons.push_back(&jun);
        activeButtons.push_back(&jul);
        activeButtons.push_back(&aug);
        activeButtons.push_back(&sep);
        activeButtons.push_back(&oct);
        activeButtons.push_back(&nov);
        activeButtons.push_back(&dec);
        activeButtons.push_back(&back);
        activeButtons.push_back(&gbackground);

        screen_num = 2;
    }

    void displayVariousStats() {
        activeButtons.push_back(&back);

        screen_num = 3;
    }

    void displayDBMGraph() {
        int graphsToShow = 0;
        for (bool x : activeMonths)
            if (x)
                graphsToShow++;

        int graphMax = -1;

        for (int x : ds.numDelaysByMonth)
            if (x > graphMax)
                graphMax = x;
        
        int scalefactor = 1;
        if (graphMax >= 10) {
            while (graphMax > 10 * 10) {
                graphMax /= 10;
                scalefactor *= 10;
            }

            scalefactor *= (graphMax / 10);
        }
        int counter = 0;
        bool highlighted = false;
        for (int i = 0; i < 12; i++) {
            sf::Sprite spr;
            sf::Sprite month;
           
            
            //if the month is active (box is checked)
            if (activeMonths[i]) {
#define GRAPH_X 550 - 18 * graphsToShow + (counter * 40)
                month.setTexture(ddtm.GetTexture(months[i]));
                month.setPosition(sf::Vector2f(GRAPH_X, 400 + 36));
                window->draw(month);
                for (int j = 0; j <= 4 * ds.numDelaysByMonth[i] / scalefactor; j++) {
                    // if the mouse is on a column. that's all this line is. seems scary, put please do not fret. that's all this line is.
                    if (sf::Rect<int>(sf::Vector2i(GRAPH_X, 406 - 24 * ds.numDelaysByMonth[i] / scalefactor), sf::Vector2i(36, 72 + 24 * ds.numDelaysByMonth[i] / scalefactor)).contains(sf::Mouse::getPosition(*window))) { // DEAR GOD
                        spr.setTexture(ddtm.GetTexture("misc-graphdata-h"));
                        highlighted = true;
                    }
                    else {
                        spr.setTexture(ddtm.GetTexture("misc-graphdata"));
                        highlighted = false;
                    }
                    spr.setPosition(sf::Vector2f(GRAPH_X, 400 - 6 * j));
                    window->draw(spr);
                }
                if (highlighted) {
                    data.setPosition(sf::Vector2f(180, 400 + 128));
                    data.setString("Number of " + month_names[i] + " delays: " + to_string(ds.numDelaysByMonth[i]));
                    window->draw(data);
                }

                counter++;
            } 
        }
    }
};

void DD_Program::Button::click() {
    /* The program will take the string name that the button has associated with it and
       do specific things based of that name. I don't know any better way to do this. */

    if (name == "but-dbd")
        screen_num = 1;
    else if (name == "but-dbm")
        screen_num = 2;
    else if (name == "but-varstts")
        screen_num = 3;
    else if (name == "but-back") 
        screen_num = 0;

    else if (name[4] == 'm' && name[5] == '-') {
        monthSwap(name);
        tex = tm.GetTexture(name);
    }
}

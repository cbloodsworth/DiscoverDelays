#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <queue>

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
    sf::Sprite clkspr1;   // these next sprites are for clickable objects
    sf::Sprite clkspr2;
    sf::Sprite clkspr3;
    sf::Sprite clkspr4;

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
    Button welc_banner;

    Button jan; Button feb; Button mar; Button apr; Button may; Button jun;
    Button jul; Button aug; Button sep; Button oct; Button nov; Button dec;

    Button back;
    
    
    //...initialize them here. String is the filename, then xpos and ypos. put true if you want them to be clickable, false if not.
    DD_Program() :  del_by_day("but-dbd", 150, 350, true),
                    del_by_month("but-dbm", 618, 350, true),
                    var_stats("but-varstts", 384, 550, true),
                    welc_banner("misc-welcbanner", 0, 50),
                    jan("but-m-jan-0", 36, 36, true),
                    feb("but-m-feb-0", 36, 72+10, true),
                    mar("but-m-mar-0", 36, 108+20, true),
                    apr("but-m-apr-0", 36, 144+30, true),
                    jun("but-m-jun-0", 36, 180+40, true),
                    jul("but-m-jul-0", 36, 216+50, true),
                    aug("but-m-aug-0", 36, 252+60, true),
                    sep("but-m-sep-0", 36, 288+70, true),
                    oct("but-m-oct-0", 36, 324+80, true),
                    nov("but-m-nov-0", 36, 360+90, true),
                    dec("but-m-dec-0", 36, 396+100, true),
                    back("but-back", 36, 700, true) {}
    
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
                    // TODO: if rectangle contains where mouse is, grrab that button
                    for (auto& b : activeButtons) {
                        if (sf::Rect<int>(b->pos, b->size).contains(sf::Mouse::getPosition(*window))) {
                            if (not b->clickable)
                                continue;
                            b->click();
                            if (screen_num == 0)
                                turnOffButtons();
                            else if (screen_num == 2)
                                exclusiveButtons(*b);

                            updateActiveMonths();
                            for (bool x : activeMonths)
                                cout << x << ",";

                            cout << endl;
                        }
                    }
                } break;

                case (sf::Event::Closed): 
                {
                    window->close();
                } break;

                }

                
            }

            
            

            displayButtons();
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

        screen_num = 2;
    }

    void displayVariousStats() {
        activeButtons.push_back(&back);

        screen_num = 3;
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

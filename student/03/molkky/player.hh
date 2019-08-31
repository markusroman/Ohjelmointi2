#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

class Player {
    public:
        Player(const std::string name);
        std::string get_name() const;
        int get_points();
        bool has_won();
        void add_points(int points_to_add);
    private:
        std::string name_;
        int points_;
};



#endif // PLAYER_HH

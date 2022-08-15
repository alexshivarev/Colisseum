#ifndef Gladiator_h
#define Gladiator_h

class Gladiator {
private:
    int gladiatorID;
    int score;

public:
    Gladiator(int const& gladiatorID, int const& score)
    : gladiatorID(gladiatorID), score(score) {}
    
    ~Gladiator(){}
    
    bool operator<(const Gladiator& rhs) const {
        if (this->score == rhs.score) {
            return (this->gladiatorID > rhs.gladiatorID);
        }
        return (this->score < rhs.score);

    }
    
};

#endif /* Gladiator_h */

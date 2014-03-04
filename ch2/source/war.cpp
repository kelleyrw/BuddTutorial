// ------------------------------- //
// Card class
// ------------------------------- //

#include <iostream>

class Card
{
    public:

        // enums
        struct Suit
        {
            enum enum_type
            {
                Diamond,
                Club,
                Heart,
                Spade,

                static_size
            };

            struct Description
            {
                const char *Name;
                const char *NamePlural;
            };
        };

        struct Rank
        {
            enum enum_type
            {
                Ace,
                Two,
                Three,
                Four,
                Five,
                Six,
                Seven,
                Eight,
                Nine,
                Ten,
                Jack,
                Queen,
                King,

                static_size
            };

            struct Description
            {
                const char *Name;
                const char *NamePlural;
            };
        };

        // construct:
        Card();
        Card(const Suit::enum_type suit, const Rank::enum_type rank);

        // methods:
        Suit::enum_type GetSuit() const; 
        const char* GetSuitName() const; 
        const char* GetSuitNamePlural() const; 

        Rank::enum_type GetRank() const; 
        const char* GetRankName() const; 
        const char* GetRankNamePlural() const; 

        // fiends:
        friend std::ostream& operator << (std::ostream& out, const Card& card);
        friend bool operator <  (const Card& lhs, const Card& rhs);
        friend bool operator == (const Card& lhs, const Card& rhs);

    private:
        // members:
        Suit::enum_type m_suit;
        Rank::enum_type m_rank;
};

// construct:
Card::Card()
    : m_suit(Card::Suit::Spade)
    , m_rank(Card::Rank::Ace)
{
}

Card::Card(const Card::Suit::enum_type suit, const Card::Rank::enum_type rank)
    : m_suit(suit)
    , m_rank(rank)
{
}

// members:
// description data
const Card::Suit::Description s_SuitDescriptions[Card::Suit::static_size] = 
{
    {"Diamond", "Diamonds"},
    {"Club"   , "Clubs"   },
    {"Heart"  , "Hearts"  },
    {"Spade"  , "Spades"  }
};

const Card::Rank::Description s_RankDescriptions[Card::Rank::static_size] = 
{
    {"Ace"   , "Aces"   }, 
    {"Two"   , "Twos"   }, 
    {"Three" , "Threes" }, 
    {"Four"  , "Fours"  },
    {"Five"  , "Fives"  },
    {"Six"   , "Sixes"  },
    {"Seven" , "Sevens" },
    {"Eight" , "Eights" },
    {"Nine"  , "Nines"  },
    {"Ten"   , "Tens"   },
    {"Jack"  , "Jacks"  },
    {"Queen" , "Queens" },
    {"King"  , "Kings"  }
};

Card::Suit::enum_type Card::GetSuit() const 
{
    return m_suit;
}

const char* Card::GetSuitName() const 
{
    return s_SuitDescriptions[m_suit].Name;
}

const char* Card::GetSuitNamePlural() const 
{
    return s_SuitDescriptions[m_suit].NamePlural;
}

Card::Rank::enum_type Card::GetRank() const
{
    return m_rank;
}

const char* Card::GetRankName() const 
{
    return s_RankDescriptions[m_rank].Name;
}

const char* Card::GetRankNamePlural() const 
{
    return s_RankDescriptions[m_rank].NamePlural;
}

// operators:
std::ostream& operator << (std::ostream& out, const Card& card)
{
    out << card.GetRankName() << " of " << card.GetSuitNamePlural();
    return out;
}

bool operator < (const Card& lhs, const Card& rhs)
{
    return (lhs.m_rank < rhs.m_rank); 
}

bool operator == (const Card& lhs, const Card& rhs)
{
    return (lhs.m_rank==rhs.m_rank);
}

void TestCard()
{
    Card c1;
    Card c2(Card::Suit::Diamond, Card::Rank::Seven);
    Card c3(Card::Suit::Diamond, Card::Rank::King );

    using namespace std;
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c3 = " << c3 << endl;
    cout << "c1 == c1 =  " << (c1 == c1) << endl;
    cout << "c1 == c2 =  " << (c2 == c1) << endl;
    cout << "c2 == c3 =  " << (c2 == c3) << endl;
    cout << "c1 < c1  =  " << (c1 < c1)  << endl;
    cout << "c1 < c2  =  " << (c2 < c1)  << endl;
    cout << "c2 < c3  =  " << (c2 < c3)  << endl;
}

// ------------------------------- //
// Deck class
// ------------------------------- //

class Deck
{
    public:
        // number of cards/deck == constant
        static const unsigned int NumCards = 52;

        // construct:
        Deck();

        // methods:
        void Shuffle();
        bool Empty() const;
        Card Draw();

    private:
        // members:
        Card m_cards[NumCards];
        unsigned int m_top_card_idx;
};

// constuct:
Deck::Deck()
    : m_cards()
    , m_top_card_idx(0)
{
    for (unsigned int rank = 0; rank != Card::Rank::static_size; rank++)
    {
        m_cards[m_top_card_idx++] = Card(Card::Suit::Diamond, static_cast<Card::Rank::enum_type>(rank));
        m_cards[m_top_card_idx++] = Card(Card::Suit::Spade  , static_cast<Card::Rank::enum_type>(rank));
        m_cards[m_top_card_idx++] = Card(Card::Suit::Club   , static_cast<Card::Rank::enum_type>(rank));
        m_cards[m_top_card_idx++] = Card(Card::Suit::Heart  , static_cast<Card::Rank::enum_type>(rank));
    }
}

// members:
#include <cstdlib>
#include <algorithm>
#include <stdexcept>

struct RandomInteger
{
    unsigned int operator() (const unsigned int max) {return std::rand() % max;}
} random_integer;

void Deck::Shuffle()
{
    std::random_shuffle(m_cards, m_cards+Deck::NumCards, random_integer);
}

bool Deck::Empty() const
{
    return (m_top_card_idx==0);
}

Card Deck::Draw()
{
    if (Empty())
    {
        throw std::runtime_error("[Deck::Draw] Deck is empty!");
    }
    return m_cards[--m_top_card_idx];
}

// ------------------------------- //
// Player class
// ------------------------------- //

class Player
{
    public:
        // construct:
        Player();
        virtual ~Player();

        // methods:
        void InitHand(Deck& deck);
        void AddPoints(const int points);
        void ReplaceCard(Deck& deck);
        virtual Card Draw();
        unsigned int Score() const;

    protected:
        // members:
        unsigned int m_score;
        unsigned int m_removed_card;
        Card m_cards[3];
};

// construct:
Player::Player()
    : m_score(0)
    , m_removed_card(0)
    , m_cards()
{
}

/*virtual*/ Player::~Player()
{
}

// methods:
void Player::InitHand(Deck& deck)
{
    m_cards[0] = deck.Draw();
    m_cards[1] = deck.Draw();
    m_cards[2] = deck.Draw();
}

void Player::AddPoints(const int points)
{
    m_score += points;
}

void Player::ReplaceCard(Deck& deck)
{
    m_cards[m_removed_card] = deck.Draw();
}

/*virtual*/ Card Player::Draw()
{
    m_removed_card = random_integer(3);
    return m_cards[m_removed_card];
}

unsigned int Player::Score() const
{
    return m_score;
}

// ------------------------------- //
// Human player class
// ------------------------------- //

class HumanPlayer : public Player
{
    public:
        virtual ~HumanPlayer();
        virtual Card Draw();
};

/*virtual*/ HumanPlayer::~HumanPlayer()
{
}

/*virtual*/ Card HumanPlayer::Draw()
{
    using std::cout;
    using std::cin;
    using std::endl;

    cout << "Your current hand is:\n";
    cout << "a) " << m_cards[0] << "\n";
    cout << "b) " << m_cards[1] << "\n";
    cout << "c) " << m_cards[2] << "\n";
    cout << "Which one do you want to play? ";
    char response;
    m_removed_card = -1;
    while (m_removed_card == -1)
    {
        cin >> response;
        switch (response)
        {
            case 'a': m_removed_card = 0; break;
            case 'b': m_removed_card = 1; break;
            case 'c': m_removed_card = 2; break;
            default:
                cout << "Please specify a, b, or c\n";
        }
    }
    return m_cards[m_removed_card];
}

// ------------------------------- //
// the game 
// ------------------------------- //

#include <tr1/memory>

class WarGame
{
	public:
        // construct:
		WarGame();

        // methods:
		void Update();
		bool IsDone() const;

	private:
		WarGame(const WarGame&); // noncopyable
		WarGame& operator = (const WarGame&); // nonassignable

        // methods:
        void SelectPlayers();
        void PrintResult() const;

		// members:
		bool m_done;
        std::tr1::shared_ptr<Player> m_player1;
        std::tr1::shared_ptr<Player> m_player2;
        Deck m_deck;
};

// construct:
WarGame::WarGame()
    : m_done(false)
    , m_player1()
    , m_player2()
    , m_deck()
{
    m_deck.Shuffle();
    SelectPlayers();
    m_player1->InitHand(m_deck);
    m_player2->InitHand(m_deck);
}

// methods:
void WarGame::SelectPlayers()
{
    using std::cout;
    using std::cin;
    using std::endl;

    cout << "Who will be Player 1:\n";
    cout << "1) computer\n";
    cout << "2) human\n";
    cout << "Please choose 1 or 2: ";
    char response = '\0';
    while (response == '\0')
    {
        cin >> response;
        switch (response)
        {
            case '1': m_player1.reset(new Player     ); break;
            case '2': m_player1.reset(new HumanPlayer); break;
            default:
                response = '\0';
                cout << "Please specify 1 or 2\n";
        }
    }

    cout << "Who will be Player 2:\n";
    cout << "1) computer\n";
    cout << "2) human\n";
    cout << "Please choose 1 or 2: ";
    response = '\0';
    while (response == '\0')
    {
        cin >> response;
        switch (response)
        {
            case '1': m_player2.reset(new Player     ); break;
            case '2': m_player2.reset(new HumanPlayer); break;
            default:
                response = '\0';
                cout << "Please specify 1 or 2\n";
        }
    }
}

void WarGame::Update()
{
    using std::cout;
    using std::endl;

    cout << "\n------- round --------\n\n";

    cout << "Player 1's turn:\n";
    Card card1 = m_player1->Draw();
    cout << "Player 1 plays " << card1 << "\n";

    cout << "Player 2's turn:\n";
    Card card2 = m_player2->Draw();
    cout << "Player 2 plays " << card2 << "\n";

    if (card1 == card2)
    {
        m_player1->AddPoints(1);
        m_player2->AddPoints(1);
        cout << "Player tie\n";
    }
    else if (card1 < card2)
    {
        m_player2->AddPoints(2);
        cout << "Player 2 wins\n";
    }
    else
    {
        m_player1->AddPoints(2);
        cout << "Player 1 wins\n";
    }

    // replace cards
    if (not m_deck.Empty()) {m_player1->ReplaceCard(m_deck);}
    if (not m_deck.Empty()) {m_player2->ReplaceCard(m_deck);}

    // check status
    m_done = m_deck.Empty();
    PrintResult();
}

bool WarGame::IsDone() const
{
    return m_done;
}

void WarGame::PrintResult() const
{
    std::cout << "Player1 score " << m_player1->Score() << "\n";
    std::cout << "Player2 score " << m_player2->Score() << "\n";
    if (IsDone())
    {
        if (m_player1->Score() > m_player2->Score())
        {
            std::cout << "Player1 wins!\n";
        }
        else
        {
            std::cout << "Player2 wins!\n";
        }
    }
}

// ------------------------------- //
// main program
// ------------------------------- //

int main()
try
{
 	WarGame game;
 	while(!game.IsDone())
 	{
 		game.Update();
 	}

	return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
}

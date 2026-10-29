#ifndef ARCADE_DECK_H
#define ARCADE_DECK_H

#include <random>

#include "card.h"

/// @file deck.h
/// @brief A deck of 52 cards that owns its memory.

/// The number of cards in a full deck.
inline constexpr int deck_size = 52;

// TODO: Write the class invariant here as a comment.
//  Say what m_cards points to, what m_size is, and what range m_next may have.
/* 
    - m_cards points to a heap that has m_size of Card objects
    - m_size is the total number of cards in the deck
    - thus m_next is in range from [0, m_size].
*/
// TODO: Explain here what goes wrong if operator= omits the self-assignment
//  check (d = d;).
/*
    - if there is no self assignment check for operator=, it will executed delete[] m_cards
    - for example: if deck a = deck a, then the memory for one deck a will be released
    - since they are the same object, the program will try to read from a deleted deck
    - thus causing errors
*/
/// A deck of playing cards stored in a heap array.
class Deck {
public:
  /// Make a full, ordered deck: one of each rank in each suit.
  /// TODO: allocate with new[] and fill in all 52 cards.
  Deck();

  /// Free the cards.
  /// TODO:
  ~Deck();

  /// Make an independent copy of another deck.
  /// TODO: A deep copy, not a copy of the pointer.
  Deck(const Deck &other);

  /// Replace this deck's contents with a copy of another deck.
  /// TODO: Free the old cards, copy the new ones, and survive d = d.
  Deck &operator=(const Deck &other);

  /// Put all the cards in random order and start dealing from the top again.
  /// @param gen the random number generator to draw from
  void shuffle(std::mt19937 &gen);

  /// Take the top card.
  /// @pre the deck is not empty
  /// @return the card that was on top
  Card deal();

  /// @return true if every card has been dealt
  // this function does not modify anything
  bool empty() const;

  /// @return how many cards are left to deal
  // this function does not modify anything
  int remaining() const;

private:
  Card *m_cards;
  int m_size;
  int m_next;
};

#endif // ARCADE_DECK_H

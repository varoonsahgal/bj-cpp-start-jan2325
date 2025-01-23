#include <gtest/gtest.h>
#include "card.h"  // Include the header for your Card class
#include "deck.hpp"  // Include the header for your Deck class
#include <iostream>
#include "player.hpp"
#include "dealer.hpp"



// Test default constructor
TEST(CardTest, DefaultConstructor) {
    Card card;
    EXPECT_EQ(card.getNumber(), 0);        // Default number should be 0
    EXPECT_EQ(card.getSuit(), '\0');      // Default suit should be '\0'
    EXPECT_FALSE(card.getBlock());        // Default block should be false
}

TEST(CardTest, ParameterizedConstructorInitializesCorrectly) {
    // 🧐 Hint: Use the parameterized constructor to create a Card object with:
    // - Specific values for `number` and `suit` as `char`.
    // - ✅ Verify that `number` and `suit` are set correctly.
    // - ⚠️ Check edge cases: invalid values for `number` (e.g., negative or >13) or `suit` (non-standard characters).
	Card card(1, 'C');
	EXPECT_EQ(card.getNumber(), 1);        // number should be 1
	EXPECT_EQ(card.getSuit(), 'C');      // suit should be 'C'
	EXPECT_FALSE(card.getBlock());        // Default block should be false

	// this is a problem!  our card class should not allow invalid cards to be created
	// it should instead throw an exception or return an error code
	Card invalidCard(14, 'Z'); // invalid number and suit
	EXPECT_EQ(invalidCard.getNumber(), 14);        // number should be 14
	EXPECT_EQ(invalidCard.getSuit(), 'Z');      // suit should be 'Z'
}

TEST(CardTest, AcceptsAndHandlesSuitCharacters) {
    // 🧐 Hint: Test how the Card class handles different `suit` values:
    // - ✅ Verify that it accepts 'H', 'D', 'C', and 'S' as valid suits.
    // - ⚠️ Check edge cases with invalid `char` values (e.g., 'Z', '!', or '0').
    // - 🤔 Consider how the class behaves when given invalid suits. Does it throw an exception? Set a default suit?

	Card heartscard(1, 'H');
	EXPECT_EQ(heartscard.getNumber(), 1);        // number should be 1
	EXPECT_EQ(heartscard.getSuit(), 'H');      // suit should be 'H'

	//this test should fail because the card class is NOT handling invalid suits
	EXPECT_THROW(Card(17, 'Z'), std::invalid_argument); // invalid suit


}

TEST(DeckTest, InitializesWithCorrectCards) {
    // 🧐 Hint: When a Deck object is initialized:
    // - ✅ Verify that all 52 cards are present (correct `number` and `suit` combinations).
    // - ✅ Check that no duplicate cards exist.
    // - ♣️ Ensure suits are represented as 'H', 'D', 'C', and 'S' only.

	Deck deck;

	deck.initializeDeck();
	EXPECT_EQ(deck.getSize(), 52); // 52 cards in a deck
     
	// check for duplicates
	auto cards = deck.getCards();
	EXPECT_EQ(cards.size(), 52); // 52 cards in a deck


	// check for correct suits
	std::vector<char> suits = { 'H', 'D', 'C', 'S' };
    
	for (const auto& suit : suits) {
		for (int i = 1; i <= 13; i++) {
			Card card(i, suit);
			//EXPECT_TRUE(std::find(cards.begin(), cards.end(), card) != cards.end());

		}
	}

    //for std::tuple<int, char>
    //    TEST(DeckTest, InitializedDeckShouldHaveAllCards) {
    //    Deck d = Deck();
    //    d.initializeDeck();

    //    // Deck should be at 52 cards at the start
    //    EXPECT_EQ(d.getSize(), 52);

    //    // Tuple for (number, suit) as key -> Card as value
    //    auto cardsDealt = std::unordered_map<std::tuple<int, char>, Card>();
    //    while (d.getSize() > 0) {
    //        Card dealtCard = d.deal();
    //        cardsDealt.insert({ dealtCard.getNumber(), dealtCard.getSuit() }, dealtCard);
    //    }

    //    // Check all cards are present
    //    bool deckIsValid = true;
    //    for (char suit : {'H', 'D', 'C', 'S'}) {
    //        for (int number = 1; number <= 13; number++) {
    //            deckIsValid &= cardsDealt.find({ suit, number }) != cardsDealt.end();
    //        }
    //    }

    //    EXPECT_TRUE(deckIsValid);
    //}

}

//Example of 3 A's:

TEST(CardTest, PrintsCardCorrectly) {
    // Arrange
    Card heartCard(1, 'H'); // Ace of Hearts
    Card clubCard(10, 'C'); // 10 of Clubs
    Card diamondCard(11, 'D'); // Jack of Diamonds
    Card spadeCard(13, 'S'); // King of Spades

    // Redirect cout to capture the output for validation
    std::ostringstream oss;

    // Act
    std::streambuf* originalCout = std::cout.rdbuf(oss.rdbuf());

    heartCard.printCardL1();
    heartCard.printCardL2();

    // Restore cout
    std::cout.rdbuf(originalCout);

    // Assert
    std::string output = oss.str();
    EXPECT_NE(output.find("| (\\/) |"), std::string::npos); // Check for Hearts' L1
    EXPECT_NE(output.find("| :\\/: |"), std::string::npos); // Check for Hearts' L2
}

// test out dealer for blackjack
// test out for 3 cards - does that register as blackjack?
// refactor the game.cpp class to use the new isBlackjack function

TEST(TDDTest, PlayerTestForBlackjack) {
    Card heartCard(1, 'H'); // Ace of Hearts
    Card clubCard(10, 'C'); // 10 of Clubs

	Player player;
	player.addCard(heartCard);
	player.addCard(clubCard);

	//EXPECT_EQ(player.getSum(), 21); // 21 is blackjack

    //TDD: we want to write a failing test first, then write min implementation for a new isBlackjack function
    // we want an isblackjack function that lives in the Human class, and we want to validate that 
	//if we create a player or a dealer, and add 2 cards, one of which is an Ace and the other is a 10, that the function returns true

	//is blackjack does not exist yet, so this will fail - our goal is to add this function to the human class
    //and do it in a TDD way!
	EXPECT_TRUE(player.isBlackjack());


    //  else if(dealer.getSum() == 21 || player.getSum() == 21){

}

TEST(TDDTest, DealerTestForBlackjack) {
    Card heartCard(1, 'H'); // Ace of Hearts
    Card clubCard(10, 'C'); // 10 of Clubs

    Dealer dealer;
    dealer.addCard(heartCard);
    dealer.addCard(clubCard);

    //EXPECT_EQ(player.getSum(), 21); // 21 is blackjack

    //TDD: we want to write a failing test first, then write min implementation for a new isBlackjack function
    // we want an isblackjack function that lives in the Human class, and we want to validate that 
    //if we create a player or a dealer, and add 2 cards, one of which is an Ace and the other is a 10, that the function returns true

    //is blackjack does not exist yet, so this will fail - our goal is to add this function to the human class
    //and do it in a TDD way!
    EXPECT_TRUE(dealer.isBlackjack());


    //  else if(dealer.getSum() == 21 || player.getSum() == 21){

}



// Example test case
TEST(ExampleTest, BasicAssertions) {
    // Expect equality
    EXPECT_EQ(1 + 1, 2);
    // Expect inequality
    EXPECT_EQ(2 * 2, 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

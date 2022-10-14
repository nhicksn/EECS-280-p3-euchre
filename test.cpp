void deal() {
        for (int i = 0; i< 4; i++) {
            if (i % 2) {
                for (int j = 0; j < 2; j++) {
                    Card c = deck.deal_one();
                    players[i]->add_card(c);
                }
            }
            else {
                for (int j = 0; j < 1; j++) {
                    Card c = deck.deal_one();
                    players[i]->add_card(c);
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            if (i % 2) {
                for (int j = 0; j < 1; j++) {
                    Card c = deck.deal_one();
                    players[i]->add_card(c);
                }
            }
            else {
                for (int j = 0; j < 2; j++) {
                    Card c = deck.deal_one();
                    players[i]->add_card(c);
                }
            }
        }
    }
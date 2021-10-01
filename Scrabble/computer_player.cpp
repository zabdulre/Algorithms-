
#include "computer_player.h"

#include <iostream>
#include <memory>
#include <string>

void ComputerPlayer::left_part(
        Board::Position anchor_pos,
        std::string partial_word,
        Move partial_move,
        std::shared_ptr<Dictionary::TrieNode> node,
        size_t limit,
        TileCollection& remaining_tiles,
        std::vector<Move>& legal_moves,
        const Board& board) const {
    // HW5: IMPLEMENT THIS
    bool questionMarkUsed = false;
    extend_right(anchor_pos, partial_word, partial_move, node, remaining_tiles, legal_moves, board);
    if (limit > 0) {
        for (std::map<char, std::shared_ptr<Dictionary::TrieNode>>::iterator cursor = node->nexts.begin();
             cursor != node->nexts.end();
             cursor++) {
            questionMarkUsed = false;
            if (is_in_rack_including_question_mark(remaining_tiles, cursor->first)) {
                try {
                    remaining_tiles.remove_tile(TileKind(cursor->first, 0));
                } catch (std::out_of_range& e) {
                    questionMarkUsed = true;
                    remaining_tiles.remove_tile(TileKind('?', 0));
                }
                std::shared_ptr<Dictionary::TrieNode> nodePrime;
                nodePrime = cursor->second;
                Move newPartialMove(
                        partial_move.tiles,
                        partial_move.row + ((partial_move.direction == Direction::DOWN) ? -1 : 0),
                        partial_move.column + ((partial_move.direction == Direction::ACROSS) ? -1 : 0),
                        partial_move.direction);
                newPartialMove.tiles.push_back(TileKind(
                        (!questionMarkUsed) ? cursor->first : '?',
                        (!questionMarkUsed) ? this->tiles.lookup_tile(cursor->first).points
                                            : this->tiles.lookup_tile('?').points));
                if (questionMarkUsed)
                    newPartialMove.tiles[newPartialMove.tiles.size() - 1].assigned = cursor->first;
                partial_word += cursor->first;
                left_part(
                        anchor_pos,
                        partial_word,
                        newPartialMove,
                        nodePrime,
                        limit - 1,
                        remaining_tiles,
                        legal_moves,
                        board);
                partial_word.pop_back();
                if (!questionMarkUsed)
                    remaining_tiles.add_tile(TileKind(cursor->first, this->tiles.lookup_tile(cursor->first).points));
                else
                    remaining_tiles.add_tile(TileKind('?', this->tiles.lookup_tile('?').points));
            }
        }
    }
    return;
}

bool ComputerPlayer::is_in_rack_including_question_mark(const TileCollection& remaining_tiles, const char c) const {
    try {
        remaining_tiles.lookup_tile('?');
        return true;
    } catch (std::out_of_range& e) {
        try {
            remaining_tiles.lookup_tile(c);
            return true;
        } catch (std::out_of_range& e) {
            return false;
        }
    }
    return false;
}

void ComputerPlayer::extend_right(
        Board::Position square,
        std::string partial_word,
        Move partial_move,
        std::shared_ptr<Dictionary::TrieNode> node,
        TileCollection& remaining_tiles,
        std::vector<Move>& legal_moves,
        const Board& board) const {
    // HW5: IMPLEMENT THIS
    bool questionMarkUsed = false;
    if (!board.is_in_bounds(square)) {
        if (node->is_final) {  // n is a terminal node
            legal_moves.push_back(partial_move);
        }
        return;
    }
    if (!board.in_bounds_and_has_tile(square)) {  // square is vaccant
        if (node->is_final) {                     // n is a terminal node
            legal_moves.push_back(partial_move);  //}
        }
        for (std::map<char, std::shared_ptr<Dictionary::TrieNode>>::iterator cursor = node->nexts.begin();
             cursor != node->nexts.end();
             cursor++) {  // for each edge
            questionMarkUsed = false;
            if (is_in_rack_including_question_mark(
                        remaining_tiles,
                        cursor->first)) {  // something about cross-checks//maybe 2 different cases//if its in our rack
                try {
                    remaining_tiles.remove_tile(TileKind(cursor->first, 0));
                } catch (std::out_of_range& e) {
                    questionMarkUsed = true;
                    remaining_tiles.remove_tile(TileKind('?', 0));
                }
                //                std::shared_ptr<Dictionary::TrieNode> nodePrime;
                //                nodePrime = cursor -> second;
                Board::Position nextSquare(
                        square.row + ((partial_move.direction == Direction::DOWN) ? 1 : 0),
                        (square.column
                         + ((partial_move.direction == Direction::ACROSS) ? 1 : 0)));  // here//add translate function
                Move newPartialMove(partial_move.tiles, partial_move.row, partial_move.column, partial_move.direction);
                newPartialMove.tiles.push_back(TileKind(
                        (!questionMarkUsed) ? cursor->first : '?',
                        (!questionMarkUsed) ? this->tiles.lookup_tile(cursor->first).points
                                            : this->tiles.lookup_tile('?').points));
                if (questionMarkUsed)
                    newPartialMove.tiles[newPartialMove.tiles.size() - 1].assigned = cursor->first;
                partial_word += cursor->first;
                extend_right(
                        nextSquare,
                        partial_word,
                        newPartialMove,
                        cursor->second,
                        remaining_tiles,
                        legal_moves,
                        board);           // call for blank tile and the actual tile if we have the tile
                partial_word.pop_back();  // might not need this
                if (!questionMarkUsed)
                    remaining_tiles.add_tile(TileKind(cursor->first, this->tiles.lookup_tile(cursor->first).points));
                else
                    remaining_tiles.add_tile(TileKind('?', this->tiles.lookup_tile('?').points));
            }
        }
    } else {
        char l = board.letter_at(square);
        bool edgeLabeledByLThatLeadsToSomeNodeN = false;
        std::map<char, std::shared_ptr<Dictionary::TrieNode>>::iterator cursor;
        cursor = node->nexts.find(l);
        if (cursor != node->nexts.end())
            edgeLabeledByLThatLeadsToSomeNodeN = true;
        if (edgeLabeledByLThatLeadsToSomeNodeN) {
            Board::Position nextSquare(
                    square.row + ((partial_move.direction == Direction::DOWN) ? 1 : 0),
                    (square.column + ((partial_move.direction == Direction::ACROSS) ? 1 : 0)));
            partial_word += l;  // here
            extend_right(nextSquare, partial_word, partial_move, cursor->second, remaining_tiles, legal_moves, board);
        }
    }
    return;
}

Move ComputerPlayer::get_move(const Board& board, const Dictionary& dictionary) const {
    std::vector<Move> legal_moves;
    std::vector<Board::Anchor> anchors = board.get_anchors();
    // HW5: IMPLEMENT THIS
    std::vector<TileKind> empty;
    TileCollection copyOfTiles(this->tiles);
    for (size_t i = 0; i < anchors.size(); i++) {
        if (anchors[i].limit > 0) {
            left_part(
                    anchors[i].position,
                    "",
                    Move(empty, anchors[i].position.row, anchors[i].position.column, anchors[i].direction),
                    dictionary.get_root(),
                    anchors[i].limit,
                    copyOfTiles,
                    legal_moves,
                    board);
        } else {
            std::shared_ptr<Dictionary::TrieNode> node = dictionary.get_root();
            Board::Position cursor(
                    anchors[i].position.row + ((anchors[i].direction == Direction::ACROSS) ? 0 : -1),
                    anchors[i].position.column + ((anchors[i].direction == Direction::ACROSS) ? -1 : 0));
            std::string partial_word;
            while (board.in_bounds_and_has_tile(cursor)) {
                partial_word.insert(0, 1, board.letter_at(cursor));
                cursor.column += (anchors[i].direction == Direction::ACROSS) ? -1 : 0;
                cursor.row += (anchors[i].direction == Direction::ACROSS) ? 0 : -1;
            }
            for (size_t c = 0; c < partial_word.size(); c++) {
                node = (node->nexts.find(partial_word[c])->second);
            }
            extend_right(
                    anchors[i].position,
                    partial_word,
                    Move(empty, anchors[i].position.row, anchors[i].position.column, anchors[i].direction),
                    node,
                    copyOfTiles,
                    legal_moves,
                    board);
        }
    }

    return get_best_move(legal_moves, board, dictionary);
}

Move ComputerPlayer::get_best_move(
        std::vector<Move> legal_moves, const Board& board, const Dictionary& dictionary) const {
    Move best_move = Move();  // Pass if no move found
    // HW5: IMPLEMENT THIS
    std::vector<std::pair<PlaceResult, Move>> results;
    for (size_t i = 0; i < legal_moves.size(); i++) {
        PlaceResult h = board.test_place(legal_moves[i]);
        bool validMove = true;
        if (h.valid) {
            for (size_t c = 0; c < h.words.size(); c++) {
                if (h.words[c].size() < minimum_word_length || !dictionary.is_word(h.words[c])) {  // minimum word
                                                                                                   // length
                    validMove = false;
                    break;
                }
            }
            if (validMove) {
                results.push_back(std::make_pair(h, legal_moves[i]));
            }
            if (validMove && (legal_moves[i].tiles.size() == this->tiles.count_tiles())) {
                results[results.size() - 1].first.points += emptyHandBonus;
            }
        }
    }
    size_t max = 0;
    for (size_t i = 0; i < results.size(); i++) {
        for (size_t c = 0; c < results[i].first.words.size(); c++) {
        }
        if ((results[max].first.points < results[i].first.points)) {
            max = i;
        }
    }
    if (results.size() != 0) {
        best_move = results[max].second;
    }
    return best_move;
}

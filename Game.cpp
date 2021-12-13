#include "Game.h"
#define BOARD_STRING_END 64

enum moveTypes { VALID, CHECK, INVALID_SRC, INVALID_DEST, CAUSE_CHECK, INVALID_INDEX, INVALID_MOVE, SAME_SRC_AND_DEST, CHECK_MATE };

Game::Game(const string& formatString) : _board(formatString.substr(0, BOARD_STRING_END)), _turn(formatString[BOARD_STRING_END] - '0') {}

Game::Game() : Game("RNBKQBNRPPPPPPPP################################pppppppprnbkqbnr1") {}

int Game::move(const string& moveString)
{
	_board.printBoard();
	Position src(moveString.substr(0, 2));
	Position dest(moveString.substr(2, 2));
	int type = moveType(src, dest);
	if (type == VALID)
	{
		_board.movePiece(src, dest);
	}
	_board.printBoard();
	if (isCheck())
	{
		_turn = !_turn;
		return CHECK;
	}
	else
	{
		_turn = !_turn;
		if (isCheck())
		{
			_turn = !_turn;
			_board.movePiece(dest, src);
			return CAUSE_CHECK;
		}
		else
		{
			if (type != VALID)
			{
				_turn = !_turn;
			}
			return type;
		}
	}
}

string Game::guiStr() const
{
	string guiStr = _board.getBoard();
	guiStr += ((int)_turn + '0');
	return guiStr;

}

Position Game::findPiece(char type) const
{
	bool found = false;
	int i, j;
	for (i = 0; i < BOARD_SIZE && !found; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			found = _board[Position(i, j)] != nullptr &&
				_board[Position(i, j)]->getType() == type;
		}
	}
	return Position(i, j);
}

bool Game::isCheck() const
{
	bool check = false;
	int type;
	Position kingPos = (_turn) ? findPiece(KING_BLACK) : findPiece(KING_WHITE);
	for (size_t i = 0; i < BOARD_SIZE && !check; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE && !check; j++)
		{
			type = moveType(Position(i, j), kingPos);
			check = type == VALID;
		}
	}
	return check;
}

int Game::moveType(const Position& src, const Position& dest) const
{
	if (src.getX() >= BOARD_SIZE || src.getY() >= BOARD_SIZE || dest.getX() >= BOARD_SIZE || dest.getY() >= BOARD_SIZE)
	{
		return INVALID_INDEX;
	}
	if (src == dest)
	{
		return SAME_SRC_AND_DEST;
	}
	if (_board[src] == nullptr || _board[src]->getColor() != _turn)
	{
		return INVALID_SRC;
	}
	if (!(_board[src]->validMove(_board, src, dest)))
	{
		return INVALID_MOVE;
	}
	if (_board[dest] != nullptr && _board[dest]->getColor() == _turn)
	{
		return INVALID_DEST;
	}
	return VALID;
}

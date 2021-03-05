
#include "ChessPiece.h"

ChessPiece::ChessPiece(char color, vec2 pos) {
    this->color = color;
    this->position = pos;
}
ChessPiece::~ChessPiece() {}

King::King(char color, vec2 pos) : ChessPiece(color, pos) { score = 0; }
Queen::Queen(char color, vec2 pos) : ChessPiece(color, pos) { score = 9; }
Rook::Rook(char color, vec2 pos) : ChessPiece(color, pos) { score = 5; }
Bishop::Bishop(char color, vec2 pos) : ChessPiece(color, pos) { score = 3; }
Knight::Knight(char color, vec2 pos) : ChessPiece(color, pos) { score = 3; }
Pawn::Pawn(char color, vec2 pos) : ChessPiece(color, pos) { score = 1; }

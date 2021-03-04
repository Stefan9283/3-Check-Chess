
#include "ChessPiece.h"

ChessPiece::ChessPiece(char color, vec2 pos) {
    this->color = color;
    this->position = pos;
}

King::King(char color, vec2 pos) : ChessPiece(color, pos) {  }
Queen::Queen(char color, vec2 pos) : ChessPiece(color, pos) { }
Rook::Rook(char color, vec2 pos) : ChessPiece(color, pos) { }
Bishop::Bishop(char color, vec2 pos) : ChessPiece(color, pos) {  }
Knight::Knight(char color, vec2 pos) : ChessPiece(color, pos) {  }
Pawn::Pawn(char color, vec2 pos) : ChessPiece(color, pos) {  }

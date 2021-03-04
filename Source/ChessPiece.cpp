//
// Created by Stefan on 04-Mar-21.
//

#include "ChessPiece.h"

ChessPiece::ChessPiece(char color, vec2 pos) {
    this->color = color;
    this->position = pos;
}

King::King(char color, vec2 pos) : ChessPiece(color, pos) { this->symbol = color == 'b' ? 0x2654 : 0x265A; }
Queen::Queen(char color, vec2 pos) : ChessPiece(color, pos) { this->symbol = color == 'b' ? 0x2655 : 0x265B; }
Rook::Rook(char color, vec2 pos) : ChessPiece(color, pos) { this->symbol = color == 'b' ? 0x2656 : 0x265C; }
Bishop::Bishop(char color, vec2 pos) : ChessPiece(color, pos) { this->symbol = color == 'b' ? 0x2657 : 0x265D; }
Knight::Knight(char color, vec2 pos) : ChessPiece(color, pos) { this->symbol = color == 'b' ? 0x2658 : 0x265E; }
Pawn::Pawn(char color, vec2 pos) : ChessPiece(color, pos) { this->symbol = color == 'b' ? 0x2659 : 0x265F; }

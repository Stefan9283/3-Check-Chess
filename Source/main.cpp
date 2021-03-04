
#include <common.h>
#include "ChessPiece.h"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"%c%c\n", Pawn('b', vec2{0, 0}).symbol, Pawn('w', vec2{0, 0}).symbol);
    return 0;
}

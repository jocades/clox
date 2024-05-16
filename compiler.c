#include "compiler.h"

#include <stdio.h>

#include "scanner.h"

typedef struct {
  Token current;
  Token previous;
  bool had_error;
  bool panic_mode;
} Parser;

Parser parser;
Chunk *compiling_chunk;

static Chunk *currentChunk() { return compiling_chunk; }

static void errorAt(Token *token, const char *msg) {
  if (parser.panic_mode) return;
  parser.panic_mode = true;
  fprintf(stderr, "[line %d] Error", token->line);

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
    // Nothing
  } else {
    fprintf(stderr, " at '%.*s'", token->length, token->start);
  }

  fprintf(stderr, ": %s\n", msg);
  parser.had_error = true;
}

static void error(const char *msg) { errorAt(&parser.previous, msg); }

static void errorAtCurrent(const char *msg) { errorAt(&parser.current, msg); }

static void advance() {
  parser.previous = parser.current;

  for (;;) {
    parser.current = scanToken();
    if (parser.current.type != TOKEN_ERROR) break;

    errorAtCurrent(parser.current.start);
  }
}

static void consume(TokenType type, const char *msg) {
  if (parser.current.type == type) {
    advance();
    return;
  }

  errorAtCurrent(msg);
}

static void emitByte(uint8_t byte) {
  writeChunk(currentChunk(), byte, parser.previous.line);
}

static void emitBytes(uint8_t byte1, uint8_t byte2) {
  emitByte(byte1);
  emitByte(byte2);
}

static void emitReturn() { emitByte(OP_RETURN); }

static void endCompiler() { emitReturn(); }

static void expression() {}

bool compile(const char *source, Chunk *chunk) {
  initScanner(source);
  compiling_chunk = chunk;

  parser.had_error = false;
  parser.panic_mode = false;

  advance();
  expression();
  consume(TOKEN_EOF, "Expected end of expression.");
  endCompiler();
  return !parser.had_error;
}

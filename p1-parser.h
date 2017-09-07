/*
   File: p1-parser.h

   	  Prototypes and structs to help parse Dutch Smart Meter P1-telegrams.
   	  
   	  (c)2017, Levien van Zon (levien at zonnetjes.net, https://github.com/lvzon)
*/

#include <inttypes.h>

// Default meter timezone is CET (The Netherlands and most of mainland Western Europe)

#define METER_TIMEZONE	"CET-1CEST,M3.5.0/2,M10.5.0/3"

// Parser buffer used to store strings

#define PARSER_BUFLEN 4096

// Parser stack length (maximum number of string/int capture-elements per line)

#define PARSER_MAXARGS 12

// Data structure used by the Ragel parser

struct parser
{
	int cs;						// Variables needed by Ragel parsers/scanners
	const char *pe;
	char *ts;
	char *te;
	int act;
		
	char buffer[PARSER_BUFLEN+1];		// String capture buffers
	int buflen;
	
	int argc;							// Integer capture stack
	long long arg[PARSER_MAXARGS];
	int multiplier;
	int bitcount;

	int strargc;						// String capture stack
	char *strarg[PARSER_MAXARGS];
	
	// Variables specific to the P1-parser
	
	uint16_t	crc16;
	char		*meter_timezone;	
};

// Function prototypes

void parser_init( struct parser *fsm );
void parser_execute(struct parser *fsm, const char *data, int len, int eofflag);
int parser_finish(struct parser *fsm);
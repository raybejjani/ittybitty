
#line 1 "http_parser.rl"
/*
 * Parse HTTP requests
 */

#include <stdio.h>
#include <string.h>

#include "http_dispatch.h"

#define BUFLEN 1024


#line 49 "http_parser.rl"



#line 20 "http_parser.c"
static const int http_parse_start = 1;
static const int http_parse_first_final = 26;
static const int http_parse_error = 0;

static const int http_parse_en_main = 1;


#line 52 "http_parser.rl"

void http_parse_init(struct http_parser_data *fsm) {
	
#line 32 "http_parser.c"
	{
	 fsm->cs = http_parse_start;
	}

#line 55 "http_parser.rl"
}

void http_parse_execute(struct http_parser_data *fsm, void* const id, const char *http_data, int len) {
	const char *p = http_data;
	const char *pe = http_data + len;

	
#line 45 "http_parser.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch (  fsm->cs )
	{
case 1:
	if ( (*p) == 71 )
		goto st2;
	goto st0;
st0:
 fsm->cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 69 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 84 )
		goto tr3;
	goto st0;
tr3:
#line 17 "http_parser.rl"
	{
		itty_http_dispatch_setVerb(id, HTTP_DISPATCH_VERB_GET);
	}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 82 "http_parser.c"
	if ( (*p) == 32 )
		goto st5;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	switch( (*p) ) {
		case 32: goto st5;
		case 47: goto tr5;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st5;
	goto st0;
tr5:
#line 20 "http_parser.rl"
	{
		itty_http_dispatch_accumPath(id, (*p));
	}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 109 "http_parser.c"
	switch( (*p) ) {
		case 32: goto st7;
		case 46: goto tr7;
		case 95: goto tr5;
	}
	if ( (*p) < 45 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st7;
	} else if ( (*p) > 47 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr5;
		} else if ( (*p) >= 65 )
			goto tr5;
	} else
		goto tr5;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 32: goto st7;
		case 49: goto st8;
		case 72: goto st17;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st7;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 46 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 49 )
		goto tr11;
	goto st0;
tr11:
#line 26 "http_parser.rl"
	{
		itty_http_dispatch_setHttpVersion(id, HTTP_DISPATCH_HTTP_VERSION_1_1);
	}
	goto st10;
tr25:
#line 23 "http_parser.rl"
	{
		itty_http_dispatch_setHttpVersion(id, HTTP_DISPATCH_HTTP_VERSION_1_0);
	}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 169 "http_parser.c"
	if ( (*p) == 13 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 10: goto st12;
		case 13: goto st26;
		case 45: goto st13;
		case 95: goto st13;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st13;
	} else if ( (*p) >= 65 )
		goto st13;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 13: goto st26;
		case 45: goto st13;
		case 95: goto st13;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st13;
	} else if ( (*p) >= 65 )
		goto st13;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	if ( (*p) == 10 )
		goto st27;
	goto st0;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	switch( (*p) ) {
		case 32: goto st14;
		case 45: goto st13;
		case 58: goto st15;
		case 95: goto st13;
	}
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st14;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st13;
	} else
		goto st13;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 32: goto st14;
		case 58: goto st15;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st14;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 32: goto st15;
		case 45: goto st16;
		case 95: goto st16;
	}
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st15;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st16;
	} else
		goto st16;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 13: goto st11;
		case 45: goto st16;
		case 95: goto st16;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st16;
	} else if ( (*p) >= 65 )
		goto st16;
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 84 )
		goto st18;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( (*p) == 84 )
		goto st19;
	goto st0;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) == 80 )
		goto st20;
	goto st0;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 47 )
		goto st21;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) == 49 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 46 )
		goto st23;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	if ( (*p) == 48 )
		goto tr25;
	goto st0;
tr7:
#line 20 "http_parser.rl"
	{
		itty_http_dispatch_accumPath(id, (*p));
	}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 338 "http_parser.c"
	switch( (*p) ) {
		case 45: goto tr26;
		case 95: goto tr26;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr26;
	} else if ( (*p) >= 65 )
		goto tr26;
	goto st0;
tr26:
#line 20 "http_parser.rl"
	{
		itty_http_dispatch_accumPath(id, (*p));
	}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 359 "http_parser.c"
	switch( (*p) ) {
		case 32: goto st7;
		case 45: goto tr26;
		case 95: goto tr26;
	}
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto st7;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr26;
	} else
		goto tr26;
	goto st0;
	}
	_test_eof2:  fsm->cs = 2; goto _test_eof; 
	_test_eof3:  fsm->cs = 3; goto _test_eof; 
	_test_eof4:  fsm->cs = 4; goto _test_eof; 
	_test_eof5:  fsm->cs = 5; goto _test_eof; 
	_test_eof6:  fsm->cs = 6; goto _test_eof; 
	_test_eof7:  fsm->cs = 7; goto _test_eof; 
	_test_eof8:  fsm->cs = 8; goto _test_eof; 
	_test_eof9:  fsm->cs = 9; goto _test_eof; 
	_test_eof10:  fsm->cs = 10; goto _test_eof; 
	_test_eof11:  fsm->cs = 11; goto _test_eof; 
	_test_eof12:  fsm->cs = 12; goto _test_eof; 
	_test_eof26:  fsm->cs = 26; goto _test_eof; 
	_test_eof27:  fsm->cs = 27; goto _test_eof; 
	_test_eof13:  fsm->cs = 13; goto _test_eof; 
	_test_eof14:  fsm->cs = 14; goto _test_eof; 
	_test_eof15:  fsm->cs = 15; goto _test_eof; 
	_test_eof16:  fsm->cs = 16; goto _test_eof; 
	_test_eof17:  fsm->cs = 17; goto _test_eof; 
	_test_eof18:  fsm->cs = 18; goto _test_eof; 
	_test_eof19:  fsm->cs = 19; goto _test_eof; 
	_test_eof20:  fsm->cs = 20; goto _test_eof; 
	_test_eof21:  fsm->cs = 21; goto _test_eof; 
	_test_eof22:  fsm->cs = 22; goto _test_eof; 
	_test_eof23:  fsm->cs = 23; goto _test_eof; 
	_test_eof24:  fsm->cs = 24; goto _test_eof; 
	_test_eof25:  fsm->cs = 25; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 62 "http_parser.rl"
}

int http_parse_finish(struct http_parser_data *fsm) {
	if ( fsm->cs == http_parse_error )
		return -1;
	if ( fsm->cs >= http_parse_first_final )
		return 1;
	return 0;
}



#line 1 "http_parser.rl"
/*
 * Parse HTTP requests
 */

#include <stdio.h>
#include <string.h>

#include "http_dispatch.h"

#define BUFLEN 1024


#line 56 "http_parser.rl"



#line 20 "http_parser.c"
static const int http_parse_start = 1;
static const int http_parse_first_final = 26;
static const int http_parse_error = 0;

static const int http_parse_en_main = 1;


#line 59 "http_parser.rl"

void http_parse_init(struct http_parser_data *fsm) {
	
#line 32 "http_parser.c"
	{
	 fsm->cs = http_parse_start;
	}

#line 62 "http_parser.rl"
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
		goto tr0;
	goto st0;
st0:
 fsm->cs = 0;
	goto _out;
tr0:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 68 "http_parser.c"
	if ( (*p) == 69 )
		goto tr2;
	goto st0;
tr2:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 82 "http_parser.c"
	if ( (*p) == 84 )
		goto tr3;
	goto st0;
tr3:
#line 22 "http_parser.rl"
	{
		itty_http_dispatch_setVerb(id, HTTP_DISPATCH_VERB_GET);
	}
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 100 "http_parser.c"
	if ( (*p) == 32 )
		goto tr4;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr4;
	goto st0;
tr4:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 116 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr4;
		case 47: goto tr5;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr4;
	goto st0;
tr5:
#line 26 "http_parser.rl"
	{
		itty_http_dispatch_accumPath(id, (*p));
	}
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 138 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr6;
		case 46: goto tr7;
		case 95: goto tr5;
	}
	if ( (*p) < 45 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto tr6;
	} else if ( (*p) > 47 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto tr5;
		} else if ( (*p) >= 65 )
			goto tr5;
	} else
		goto tr5;
	goto st0;
tr6:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 166 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr6;
		case 49: goto tr8;
		case 72: goto tr9;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr6;
	goto st0;
tr8:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 185 "http_parser.c"
	if ( (*p) == 46 )
		goto tr10;
	goto st0;
tr10:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 199 "http_parser.c"
	if ( (*p) == 49 )
		goto tr11;
	goto st0;
tr11:
#line 33 "http_parser.rl"
	{
		itty_http_dispatch_setHttpVersion(id, HTTP_DISPATCH_HTTP_VERSION_1_1);
	}
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st10;
tr25:
#line 30 "http_parser.rl"
	{
		itty_http_dispatch_setHttpVersion(id, HTTP_DISPATCH_HTTP_VERSION_1_0);
	}
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 227 "http_parser.c"
	if ( (*p) == 13 )
		goto tr12;
	goto st0;
tr12:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 241 "http_parser.c"
	switch( (*p) ) {
		case 10: goto tr13;
		case 13: goto tr14;
		case 45: goto tr15;
		case 95: goto tr15;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr15;
	} else if ( (*p) >= 65 )
		goto tr15;
	goto st0;
tr13:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 264 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr14;
		case 45: goto tr15;
		case 95: goto tr15;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr15;
	} else if ( (*p) >= 65 )
		goto tr15;
	goto st0;
tr14:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 286 "http_parser.c"
	if ( (*p) == 10 )
		goto tr27;
	goto st0;
tr27:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st27;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
#line 300 "http_parser.c"
	goto st0;
tr15:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 312 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr16;
		case 45: goto tr15;
		case 58: goto tr17;
		case 95: goto tr15;
	}
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto tr16;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr15;
	} else
		goto tr15;
	goto st0;
tr16:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 338 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr16;
		case 58: goto tr17;
	}
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr16;
	goto st0;
tr17:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 356 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr17;
		case 45: goto tr18;
		case 95: goto tr18;
	}
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto tr17;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr18;
	} else
		goto tr18;
	goto st0;
tr18:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 381 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr12;
		case 45: goto tr18;
		case 95: goto tr18;
	}
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr18;
	} else if ( (*p) >= 65 )
		goto tr18;
	goto st0;
tr9:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 403 "http_parser.c"
	if ( (*p) == 84 )
		goto tr19;
	goto st0;
tr19:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 417 "http_parser.c"
	if ( (*p) == 84 )
		goto tr20;
	goto st0;
tr20:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 431 "http_parser.c"
	if ( (*p) == 80 )
		goto tr21;
	goto st0;
tr21:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 445 "http_parser.c"
	if ( (*p) == 47 )
		goto tr22;
	goto st0;
tr22:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 459 "http_parser.c"
	if ( (*p) == 49 )
		goto tr23;
	goto st0;
tr23:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 473 "http_parser.c"
	if ( (*p) == 46 )
		goto tr24;
	goto st0;
tr24:
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 487 "http_parser.c"
	if ( (*p) == 48 )
		goto tr25;
	goto st0;
tr7:
#line 26 "http_parser.rl"
	{
		itty_http_dispatch_accumPath(id, (*p));
	}
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 505 "http_parser.c"
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
#line 26 "http_parser.rl"
	{
		itty_http_dispatch_accumPath(id, (*p));
	}
#line 18 "http_parser.rl"
	{
		itty_http_dispatch_accumReq(id, (*p));
	}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 530 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr6;
		case 45: goto tr26;
		case 95: goto tr26;
	}
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto tr6;
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

#line 69 "http_parser.rl"
}

int http_parse_finish(struct http_parser_data *fsm) {
	if ( fsm->cs == http_parse_error )
		return -1;
	if ( fsm->cs >= http_parse_first_final )
		return 1;
	return 0;
}


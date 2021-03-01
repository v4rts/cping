#ifndef CPING_ERRORS
/* Create socket errors */
const int FD_NOT_RECEIVED = -100;
const int TTL_NOT_SET     = -101;
const int TIMEOUT_NOT_SET = -102;
/* End */

/* ICMP send and receive errors */
const int SENT_FAILED     = 200;
const int RCV_FAILED      = 201;
/* End */

/* Main errors */
const int NO_ADDR      = 211;
const int ARGS_NOT_VALID  = 212;
const int UNKNOWN_ERROR   = 255;
/* End */
#endif
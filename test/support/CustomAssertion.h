#ifndef CustomAssertion_H
#define CustomAssertion_H

#include "unity.h"

#define CUSTOM_TEST_FAIL(lineNo, msg, ...)                                        \
                {                                                                 \
                char buffer[256];                                                 \
                sprintf(buffer, msg, ## __VA_ARGS__);                             \
                UNITY_TEST_FAIL(lineNo, buffer);                                  \
                }
                
                
#define TEST_ASSERT_ARRAY(expected, current, numOfElem)       \
                 customTestAssertArray(expected, current, numOfElem, __LINE__);
                 
void customTestAssertArray(int *expected, int *current, int numOfElem, int lineNo);


#endif // CustomAssertion_H

/* DOMINION
 * David Mally, Richard Roberts
 * JsonRPC.cpp
 * Defines functions for making and parsing JSON requests
 * to the Random.org JSON RPC API.
 */
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include "JsonRPC.h"
#include "Defs.h"

json_rpc::JsonResponse::JsonResponse(int reqsLeft, std::vector<int> randVals) {
    m_reqsLeft = reqsLeft;
    m_randVals = randVals;
}

json_rpc::JsonResponse json_rpc::GetJsonResult(std::string method, int numVals, int minVal,
                          int maxVal, bool replacement) {
    std::string cmd = "python2 src/python/json_rpc.py ";
    cmd += method + " ";
    cmd += std::to_string(numVals) + " ";
    cmd += std::to_string(minVal) + " ";
    cmd += std::to_string(maxVal) + " ";
    cmd += std::to_string(replacement) + " ";
    cmd += std::to_string(baseId++);

    /* This section of code borrowed from StackOverflow */
    FILE *pipe = popen(cmd.c_str(), "r");
    if(!pipe) {
        std::vector<int> v;
        return json_rpc::JsonResponse(-1, v);
    }
    char buf[MAX_BUF_LEN];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buf, MAX_BUF_LEN, pipe) != NULL) {
            result += buf;
        }
    }
    pclose(pipe);
    /* This section of code borrowed from StackOverflow */

    int tmp = -1;
    int reqsLeft = -1;
    std::vector<int> randIndexes;

    // Parse number of API requests left
    std::string bufStr = result.substr(0, result.find(' '));
    sscanf(bufStr.c_str(), "%d", &reqsLeft);
    result = result.substr(result.find(' ') + 1, result.length());

    // Parse result of API call
    for(int i = 0; i < numVals; i++) {
        bufStr = result.substr(0, result.find(' '));
        sscanf(bufStr.c_str(), "%d", &tmp);
        if(result.find(' ') != std::string::npos) {
            result = result.substr(result.find(' ') + 1, result.length());
        } else {
            result = "";
        }
        randIndexes.push_back(tmp);
    }
    return json_rpc::JsonResponse(reqsLeft, randIndexes);
}


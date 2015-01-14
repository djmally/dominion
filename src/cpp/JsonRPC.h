/* DOMINION
 * David Mally, Richard Roberts
 * JsonRPC.h
 * Defines JsonResponse tuple class for storing JSON responses
 * from RPC. Also defines method to get JSON results from Random.org
 */
#ifndef __JSONRPC_H__
#define __JSONRPC_H__

#include <string>
#include <cstdbool>
#include <vector>

namespace json_rpc {
    static int baseId = 0;

    class JsonResponse {
        private:
        public:
            int m_reqsLeft;
            std::vector<int> m_randVals;
            JsonResponse(int reqsLeft, std::vector<int> randVals);
    };

    JsonResponse GetJsonResult(std::string method, int numVals, int minVal,
                              int maxVal, bool replacement);
}

#endif

#!/usr/bin/python2

import json
import requests
import sys

api_key = "f13ce949-af39-4cb7-90bd-838767c86ac6";
target_url = "https://api.random.org/json-rpc/1/invoke"

def pack_json(method, num_vals, min_val, max_val, replacement, uid):
    params = {}
    params["apiKey"] = api_key
    params["n"] = num_vals
    params["min"] = min_val
    params["max"] = max_val
    params["replacement"] = replacement

    request_obj = {}
    request_obj["jsonrpc"] = "2.0"
    request_obj["method"] = method
    request_obj["params"] = params
    request_obj["id"] = uid
    return json.dumps(request_obj)

def send_json_request(json_dump):
    req = requests.get(target_url, data=json_dump)
    req_json = req.json()
    reqs_left = req_json['result']['requestsLeft']
    rand_vals = req_json['result']['random']['data']
    rpc_package = [reqs_left]
    rpc_package.extend([r for r in rand_vals])
    return str(rpc_package).replace(",", "").replace("[","").replace("]","")

def main():
    method = sys.argv[1]
    num_vals = int(sys.argv[2])
    min_val = int(sys.argv[3])
    max_val = int(sys.argv[4])
    replacement = sys.argv[5]
    uid = int(sys.argv[6])
    json_dump = pack_json(method, num_vals, min_val, max_val, replacement, uid)
    print(send_json_request(json_dump))

if __name__ == "__main__":
    main()


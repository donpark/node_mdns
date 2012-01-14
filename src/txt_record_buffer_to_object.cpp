#include <vector>

#include <iostream>

#include <node.h>
#include <node_buffer.h>

#include "mdns_utils.hpp"
#include "txt_record_ref.hpp"

using namespace v8;
using namespace node;

namespace node_mdns {

Handle<Value>
txtRecordBufferToObject(Arguments const& args) {
    HandleScope scope;
    if (argumentCountMismatch(args, 2)) {
        return throwArgumentCountMismatchException(args, 2);
    }
    if ( ! args[0]->IsObject() || ! Buffer::HasInstance(args[0]->ToObject())) {
        return throwTypeError("argument 1 must be a buffer (txtRecord)");
    }
    Local<Object> buffer = args[0]->ToObject();

    Local<Object> result = Object::New();
    std::vector<char> key(16);
    size_t buffer_length = Buffer::Length(buffer);
    void * data = Buffer::Data(buffer);
    uint16_t item_count = TXTRecordGetCount(buffer_length, data);
    DNSServiceErrorType error;
    const void ** value_ptr;
    uint8_t value_length;
    for (uint16_t i = 0; i < item_count; ++i) {
        error = TXTRecordGetItemAtIndex(buffer_length, data, i, key.size(), &*key.begin(), & value_length, value_ptr);
        std::cerr << "TODO" << std::endl;
    }
    return Undefined();
}

} // end of namespace node_mdns

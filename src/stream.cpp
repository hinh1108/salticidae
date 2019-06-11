#include "salticidae/config.h"
#ifdef SALTICIDAE_CBINDINGS
#include "salticidae/stream.h"

extern "C" {

uint256_t *uint256_new() { return new uint256_t(); }
uint256_t *uint256_new_from_bytes(const uint8_t *arr) {
    return new uint256_t(arr);
}
void uint256_free(const uint256_t *self) { delete self; }

bool uint256_is_null(const uint256_t *self) { return self->is_null(); }
bool uint256_is_eq(const uint256_t *a, const uint256_t *b) {
    return *a == *b;
}

void uint256_serialize(const uint256_t *self, datastream_t *s) {
    self->serialize(*s);
}

void uint256_unserialize(uint256_t *self, datastream_t *s) {
    self->unserialize(*s);
}

datastream_t *datastream_new() { return new datastream_t(); }
datastream_t *datastream_new_from_bytes(const uint8_t *begin, const uint8_t *end) {
    return new datastream_t(begin, end);
}
void datastream_free(const datastream_t *self) { delete self; }

void datastream_assign_by_copy(datastream_t *dst, const datastream_t *src) {
    *dst = *src;
}

void datastream_assign_by_move(datastream_t *dst, datastream_t *_moved_src) {
    *dst = std::move(*_moved_src);
    delete _moved_src;
}

uint8_t *datastream_data(datastream_t *self) { return self->data(); }

void datastream_clear(datastream_t *self) { self->clear(); }

size_t datastream_size(const datastream_t *self) { return self->size(); }

void datastream_put_u8(datastream_t *self, uint8_t val) { *self << val; }
void datastream_put_u16(datastream_t *self, uint16_t val) { *self << val; }
void datastream_put_u32(datastream_t *self, uint32_t val) { *self << val; }
void datastream_put_u64(datastream_t *self, uint64_t val) { *self << val; }

void datastream_put_i8(datastream_t *self, int8_t val) { *self << val; }
void datastream_put_i16(datastream_t *self, int16_t val) { *self << val; }
void datastream_put_i32(datastream_t *self, int32_t val) { *self << val; }
void datastream_put_i64(datastream_t *self, int64_t val) { *self << val; }

void datastream_put_data(datastream_t *self,
                        const uint8_t *begin, const uint8_t *end) {
    self->put_data(begin, end);
}

uint8_t datastream_get_u8(datastream_t *self) { uint8_t val; *self >> val; return val; }
uint16_t datastream_get_u16(datastream_t *self) { uint16_t val; *self >> val; return val; }
uint32_t datastream_get_u32(datastream_t *self) { uint32_t val; *self >> val; return val; }
uint64_t datastream_get_u64(datastream_t *self) { uint64_t val; *self >> val; return val; }

int8_t datastream_get_i8(datastream_t *self) { int8_t val; *self >> val; return val; }
int16_t datastream_get_i16(datastream_t *self) { int16_t val; *self >> val; return val; }
int32_t datastream_get_i32(datastream_t *self) { int32_t val; *self >> val; return val; }
int64_t datastream_get_i64(datastream_t *self) { int64_t val; *self >> val; return val; }

const uint8_t *datastream_get_data_inplace(datastream_t *self, size_t len) {
    return self->get_data_inplace(len);
}

uint256_t *datastream_get_hash(const datastream_t *self) {
    return new uint256_t(self->get_hash());
}

bytearray_t *bytearray_new_moved_from_datastream(datastream_t *_moved_src) {
    auto res = new bytearray_t(std::move(*_moved_src));
    delete _moved_src;
    return res;
}

char *datastream_get_hex(datastream_t *self) {
    std::string tmp = self->get_hex();
    auto res = (char *)malloc(tmp.length() + 1);
    memmove(res, tmp.c_str(), tmp.length());
    res[tmp.length()] = 0;
    return res;
}

}

#endif

/* This file is part of the dynarmic project.
 * Copyright (c) 2016 MerryMage
 * This software may be used and distributed according to the terms of the GNU
 * General Public License version 2 or any later version.
 */

#include "common/common_types.h"
#include "frontend/arm/types.h"
#include "frontend/decoder/coprocessor.h"
#include "frontend/decoder/decoder_detail.h"
#include "frontend/decoder/matcher.h"

namespace Dynarmic {
namespace Coprocessor {

template <typename T>
auto GetMemberFunctionOfLambda(T) {
    return &T::operator();
}

#define MAKE_MATCHER(name, bitstring) (Arm::detail::detail<Arm::Matcher<decltype(visitor), u32>>::GetMatcher(GetMemberFunctionOfLambda(visitor), name, bitstring))

void DecodeCDP(u32 instruction, std::function<void(bool two, size_t opc1, CoprocReg CRn, CoprocReg CRd, Coprocessor coproc, size_t opc2, CoprocReg CRm)> callback) {
    auto visitor = [&](Arm::Cond cond, size_t opc1, CoprocReg CRn, CoprocReg CRd, Coprocessor coproc, size_t opc2, CoprocReg CRm) {
        callback(cond == Arm::Cond::NV, opc1, CRn, CRd, coproc, opc2, CRm);
    };
    const static auto matcher = MAKE_MATCHER("CDP", "cccc1110ooooNNNNDDDDppppooo0MMMM");
    matcher.call(visitor, instruction);
}

void DecodeLDC(u32 instruction, std::function<void(bool two, bool p, bool u, bool d, bool w, ArmReg n, CoprocReg CRd, Coprocessor coproc, u8 imm8)> callback) {
    auto visitor = [&](Arm::Cond cond, bool p, bool u, bool d, bool w, ArmReg n, CoprocReg CRd, Coprocessor coproc, u8 imm8) {
        callback(cond == Arm::Cond::NV, p, u, d, w, n, CRd, coproc, imm8);
    };
    const static auto matcher = MAKE_MATCHER("LDC", "cccc110pudw1nnnnDDDDppppvvvvvvvv");
    matcher.call(visitor, instruction);
}

void DecodeSTC(u32 instruction, std::function<void(bool two, bool p, bool u, bool d, bool w, ArmReg n, CoprocReg CRd, Coprocessor coproc, u8 imm8)> callback) {
    auto visitor = [&](Arm::Cond cond, bool p, bool u, bool d, bool w, ArmReg n, CoprocReg CRd, Coprocessor coproc, u8 imm8) {
        callback(cond == Arm::Cond::NV, p, u, d, w, n, CRd, coproc, imm8);
    };
    const static auto matcher = MAKE_MATCHER("STC", "cccc110pudw0nnnnDDDDppppvvvvvvvv");
    matcher.call(visitor, instruction);
}

void DecodeMCR(u32 instruction, std::function<void(bool two, size_t opc1, CoprocReg CRn, ArmReg t, Coprocessor coproc, size_t opc2, CoprocReg CRm)> callback) {
    auto visitor = [&](Arm::Cond cond, size_t opc1, CoprocReg CRn, ArmReg t, Coprocessor coproc, size_t opc2, CoprocReg CRm) {
        callback(cond == Arm::Cond::NV, opc1, CRn, t, coproc, opc2, CRm);
    };
    const static auto matcher = MAKE_MATCHER("MCR", "cccc1110ooo0NNNNttttppppooo1MMMM");
    matcher.call(visitor, instruction);
}

void DecodeMCRR(u32 instruction, std::function<void(bool two, ArmReg t2, ArmReg t, Coprocessor coproc, size_t opc, CoprocReg CRm)> callback) {
    auto visitor = [&](Arm::Cond cond, ArmReg t2, ArmReg t, Coprocessor coproc, size_t opc, CoprocReg CRm) {
        callback(cond == Arm::Cond::NV, t2, t, coproc, opc, CRm);
    };
    const static auto matcher = MAKE_MATCHER("MCRR", "cccc11000100uuuuttttppppooooMMMM");
    matcher.call(visitor, instruction);
}

void DecodeMRC(u32 instruction, std::function<void(bool two, size_t opc1, CoprocReg CRn, ArmReg t, Coprocessor coproc, size_t opc2, CoprocReg CRm)> callback) {
    auto visitor = [&](Arm::Cond cond, size_t opc1, CoprocReg CRn, ArmReg t, Coprocessor coproc, size_t opc2, CoprocReg CRm) {
        callback(cond == Arm::Cond::NV, opc1, CRn, t, coproc, opc2, CRm);
    };
    const static auto matcher = MAKE_MATCHER("MRC", "cccc1110ooo1NNNNttttppppooo1MMMM");
    matcher.call(visitor, instruction);
}

void DecodeMRRC(u32 instruction, std::function<void(bool two, ArmReg t2, ArmReg t, Coprocessor coproc, size_t opc, CoprocReg CRm)> callback) {
    auto visitor = [&](Arm::Cond cond, ArmReg t2, ArmReg t, Coprocessor coproc, size_t opc, CoprocReg CRm) {
        callback(cond == Arm::Cond::NV, t2, t, coproc, opc, CRm);
    };
    const static auto matcher = MAKE_MATCHER("MRRC", "cccc11000101uuuuttttppppooooMMMM");
    matcher.call(visitor, instruction);
}

} // namespace Coprocessor
} // namespace Dynarmic

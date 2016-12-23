/* This file is part of the dynarmic project.
 * Copyright (c) 2016 MerryMage
 * This software may be used and distributed according to the terms of the GNU
 * General Public License version 2 or any later version.
 */

#pragma once

#include <cstdint>
#include <cstddef>
#include <functional>

namespace Dynarmic {
namespace Coprocessor {

enum class ArmReg {
    R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15,
    SP = R13,
    LR = R14,
    PC = R15
};

enum class CoprocReg {
    C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15
};

enum class Coprocessor {
    P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15
};

void DecodeCDP(std::uint32_t instruction, std::function<void(bool two, std::size_t opc1, CoprocReg CRn, CoprocReg CRd, Coprocessor coproc, std::size_t opc2, CoprocReg CRm)> callback);
void DecodeLDC(std::uint32_t instruction, std::function<void(bool two, bool p, bool u, bool d, bool w, ArmReg n, CoprocReg CRd, Coprocessor coproc, std::uint8_t imm8)> callback);
void DecodeSTC(std::uint32_t instruction, std::function<void(bool two, bool p, bool u, bool d, bool w, ArmReg n, CoprocReg CRd, Coprocessor coproc, std::uint8_t imm8)> callback);
void DecodeMCR(std::uint32_t instruction, std::function<void(bool two, std::size_t opc1, CoprocReg CRn, ArmReg t, Coprocessor coproc, std::size_t opc2, CoprocReg CRm)> callback);
void DecodeMCRR(std::uint32_t instruction, std::function<void(bool two, ArmReg t2, ArmReg t, Coprocessor coproc, std::size_t opc, CoprocReg CRm)> callback);
void DecodeMRC(std::uint32_t instruction, std::function<void(bool two, std::size_t opc1, CoprocReg CRn, ArmReg t, Coprocessor coproc, std::size_t opc2, CoprocReg CRm)> callback);
void DecodeMRRC(std::uint32_t instruction, std::function<void(bool two, ArmReg t2, ArmReg t, Coprocessor coproc, std::size_t opc, CoprocReg CRm)> callback);

} // namespace Coprocessor
} // namespace Dynarmic

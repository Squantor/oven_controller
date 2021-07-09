/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef BOARD_HPP
#define BOARD_HPP

#if defined(proto_board)
    #include <proto_board.hpp>
#else
    #error "unknown board!"
#endif

void boardInit(void);

#endif

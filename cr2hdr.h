struct xy { int x; int y; };
        const struct
        {
            struct xy ack;      /* verification pixel near a */
            struct xy a;        /* interpolation pixel from the nearby line: normally (0,s) but also (1,s) or (-1,s) */
            struct xy b;        /* interpolation pixel from the other line: normally (0,-2s) but also (1,-2s), (-1,-2s), (2,-2s) or (-2,-2s) */
            struct xy bck;      /* verification pixel near b */
        }
        edge_directions[] = {       /* note: all y coords should be multiplied by s */
            //~ { {-6,2}, {-3,1}, { 6,-2}, { 9,-3} },     /* almost horizontal (little or no improvement) */
            { {-4,2}, {-2,1}, { 4,-2}, { 6,-3} },
            { {-3,2}, {-1,1}, { 3,-2}, { 4,-3} },
            { {-2,2}, {-1,1}, { 2,-2}, { 3,-3} },     /* 45-degree diagonal */
            { {-1,2}, {-1,1}, { 1,-2}, { 2,-3} },
            { {-1,2}, { 0,1}, { 1,-2}, { 1,-3} },
            { { 0,2}, { 0,1}, { 0,-2}, { 0,-3} },     /* vertical, preferred; no extra confirmations needed */
            { { 1,2}, { 0,1}, {-1,-2}, {-1,-3} },
            { { 1,2}, { 1,1}, {-1,-2}, {-2,-3} },
            { { 2,2}, { 1,1}, {-2,-2}, {-3,-3} },     /* 45-degree diagonal */
            { { 3,2}, { 1,1}, {-3,-2}, {-4,-3} },
            { { 4,2}, { 2,1}, {-4,-2}, {-6,-3} },
            //~ { { 6,2}, { 3,1}, {-6,-2}, {-9,-3} },     /* almost horizontal */
        };
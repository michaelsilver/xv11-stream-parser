/*
 * This file is part of XV-11 Parser
 *
 * XV-11 Parser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PARSER_H_

#include <vector>
#include <string>

using std::vector;
using std::string;

class parser {
/* public functions */
public:
    /*!
     * Constructs a parser object
     * @param name Name of the window
     * @param gui whether or not to show a GUI
     */
    parser(const char *name, int delayTime = 1);

    /*!
     * Destructs a parser object
     */
    virtual ~parser();

    /*!
     * Sets the verbosity of the program
     * @param verbose bitmask for verbosity
     */
    void setVerbosity(int verbose);

    /*!
     * Call with new characters to get them parsed
     * @param c character to parse
     */
    void update(char c);

/* private functions */
private:
    /*!
     * Checks if there is a header at a given position
     * @param pos the position to check for a header
     * @return true if pos is the beginning of a header
     */
    bool is_header(int pos);

    /*!
     * Checks if there is a footer ending at a given position
     * @param pos the position to check for a footer
     * @return true if pos is the end of a footer
     */
    bool is_footer(int pos);

    /*!
     * Processes a message
     */
    void processMsg();

    /*!
     * Processes an odometry message
     */
    void processOdom();

    /*!
     * Processes a text message
     */
    void processText();

    /*!
     * Processes a laser message
     */
    void processLaser();

    /*!
     * Constructs a long, LSB first.
     * @param pos the position in the message buffer
     * @return the constructed long
     */
    long construct_long(int pos);

    /*!
     * Constructs an int, LSB first.
     * @param pos the position in the message buffer
     * @return the constructed int
     */
    int construct_int(int pos);

    enum MSG_PKT {
        HEAD        = 0x00,
        TYPE        = 0x04,
        SEQUENCE    = 0x06,
        TIMESTAMP   = 0x08,
        /* text messages */
        STR_LEN     = 0x0c,
        STR_DATA    = 0x10,
        /* laser */
        LSR_INDEX   = 0x10,
        LSR_DATA    = 0x14,
        /* map */
        MAP_SIZE    = 0x0c,
        MAP_ADDR    = 0x10,
        MAP_DATA    = 0x18,
        /* odom */
    };

    enum MSG_TYPES {
        POSITION    = 0x01,
        LASER       = 0x05,
        TEXT        = 0x11,
    };

    vector<unsigned char> m_buf;
    string m_name;

    struct laser_unit {
        int x;
        int y;
        bool valid;
    };

    struct laser_unit m_laser[360];

    struct odom_data {
        double count;
        double speed;
    };

    struct odom_data left;
    struct odom_data right;

public:
    enum VERBOSITY_LVL {
        VERB_DEBUG  = (1 << 0),
        VERB_TEXT   = (1 << 1),
        VERB_LASER  = (1 << 2),
        VERB_MAP    = (1 << 3),
        VERB_ODOM   = (1 << 4),
    };
private:

    int m_verbose;
    int m_delay_time;
};

#endif /* PARSER_H_ */

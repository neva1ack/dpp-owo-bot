#include <dpp/dpp.h>

#include <random>
#include <regex>

const std::string BOT_TOKEN = "<your bot token here>";

std::string owoify(const std::string_view &in) {
    std::string sub = std::string(in);
    // do word substitutions with regexes
    // substitute "the" with "da"
    static std::regex the_regex("(?:^|\\b)the(?:\\b|$)",
                                std::regex_constants::icase);
    sub = std::regex_replace(sub, the_regex, "da");

    // substitute "have" and "has" with "haz"
    static std::regex have_regex("(?:^|\\b)(?:have|has)(?:\\b|$)",
                                 std::regex_constants::icase);
    sub = std::regex_replace(sub, have_regex, "haz");

    // substitute "you" with "uu"
    static std::regex you_regex("(?:^|\\b)you(?:\\b|$)",
                                std::regex_constants::icase);
    sub = std::regex_replace(sub, you_regex, "uu");

    // substitute "no", "nah" and "nope" with "nu"
    static std::regex no_regex("(?:^|\\b)(?:no|nah|nope)(?:\\b|$)",
                               std::regex_constants::icase);
    sub = std::regex_replace(sub, no_regex, "nu");

    // do character substitutions
    for (auto it = sub.begin(); it != sub.end(); ++it) {
        switch (*it) {
        case 'R':
        case 'L':
            *it = 'W';
            break;
        case 'r':
        case 'l':
            *it = 'w';
            break;
        case 'V':
            *it = 'B';
            break;
        case 'v':
            *it = 'b';
            break;
        }
    }

    return sub;
}

int main() {
    dpp::cluster bot(BOT_TOKEN);

    // static array of owos
    std::array<std::string, 74> owos = {
        "owo", "OwO", "uwu",   "nwn", "^w^", ">w<",   "Owo", "owO",   ";w;",
        "0w0", "QwQ", "TwT",   "-w-", "$w$", "@w@",   "*w*", ":w:",   "°w°",
        "ºwº", "ówò", "òwó",   "`w´", "´w`", "~w~",   "umu", "nmn",   "own",
        "nwo", "ùwú", "úwù",   "ñwñ", "UwU", "NwN",   "ÙwÚ", "PwP",   "own",
        "nwo", "/w/", "\\w\\", "|w|", "#w#", "<>w<>", "'w'", "\"w\"", "öwö",
        "ôwô", "ÖwÖ", "ÔwÔ",   ".w.", "+w+", ")w(",   "]w[", "}w{",   "_w_",
        "=w=", "!w!", "YwY",   "vwv", "VwV", "<w>",   "çwç", "ÇwÇ",   ">w>",
        "<w<", "—w—", "→w→",   "→w←", "←w←", "KwK",   "GwG", "gwg",   "qwq",
        "AwA", "awa"};

    // int distrubition function
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, owos.size() - 1);

    // set logger to stdout
    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand(
        [&owos, &distr, &gen](const dpp::slashcommand_t &event) {
            // on "/owo"
            if (event.command.get_command_name() == "owo") {
                // get passed "msg" param
                auto msg = std::get<std::string>(event.get_parameter("msg"));
                // reply to command with owo-ified message and a randomly
                // selected owo face
                event.reply(owoify(msg) + " " + owos.at(distr(gen)));
            }
        });

    bot.on_ready([&bot](const dpp::ready_t &event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            // "owo" command
            dpp::slashcommand owo_command("owo", "Owo-ify your message!",
                                          bot.me.id);
            // parameter "msg"
            owo_command.add_option(dpp::command_option(
                dpp::co_string, "msg", "Message to wrap.", true));
            bot.global_command_create(owo_command);
        }
    });

    bot.start(dpp::st_wait);
}

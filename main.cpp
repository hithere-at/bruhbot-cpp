#include <dpp/dpp.h>
#include <string>
#include <cstring>

#include "modules/media.hpp"
#include "modules/utils.hpp"

const std::unordered_map env_var= get_env_vars("./.env");
const std::string TOKEN = env_var["BOT_TOKEN"];
const dpp::snowflake guild_base(env_var["GUILD_BASE_ID"]);

int main(int argc, char* argv[]) {

    dpp::cluster bot(TOKEN, dpp::intents::i_default_intents | dpp::intents::i_message_content);
    bot.on_log(dpp::utility::cout_logger());

    // on ready event. registers all command and delete all comands if specfied
    bot.on_ready([&bot, argv](const dpp::ready_t& event) {

        // run once and check if the first argument is "delete"
        if (dpp::run_once<struct clear_bot_commands>() && strncmp(argv[1], "delete", 6) == 0) {
            auto time_now = std::chrono::system_clock::now();
            std::cout << std::format("[{:%Y-%m-%d %H:%M:%S}] INFO: Command deletion has been invoked", time_now) << std::endl;

            bot.global_bulk_command_delete();
            bot.guild_bulk_command_delete(guild_base);

        }

        // register commands
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.guild_command_create(dpp::slashcommand("ping", "Check online status", bot.me.id), guild_base);
            bot.guild_command_create(dpp::slashcommand("fih", "phishe", bot.me.id), guild_base);
            bot.guild_command_create(dpp::slashcommand("fihgam", "phishe game", bot.me.id), guild_base);
            bot.guild_command_create(dpp::slashcommand("doorknob", "Flavored doorknob testing facility", bot.me.id), guild_base);
            bot.guild_command_create(dpp::slashcommand("men", "how?", bot.me.id), guild_base);

        }

    });

    // doesnt do anything except reply to message if a user tries to reply to this bot messages
    bot.on_message_create([&bot](const dpp::message_create_t& msg_event) {

        dpp::snowflake og_channel_id = msg_event.msg.message_reference.channel_id;
        dpp::snowflake og_msg_id = msg_event.msg.message_reference.message_id;
        dpp::snowflake bot_id = bot.me.id;

        // message_get() will be used because replies is message_ref type and only contains IDs, but we can get the message by using msg and channel IDs
        bot.message_get(og_msg_id, og_channel_id, [msg_event, bot_id](const dpp::confirmation_callback_t& callback) {

            if (!callback.is_error()) {
                dpp::message og_msg = std::get<dpp::message>(callback.value);
                if (og_msg.author.id == bot_id) msg_event.reply("Why are you replying to my message?");

            }

        });

    });

    // ping command
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {

        if (event.command.get_command_name() == "ping") {
            std::string reply_msg = std::format("Request completed at {:.0f}ms", bot.rest_ping * 1000);

            event.reply(reply_msg);
        }

    });

    // media commands. refer to modules/media.cpp for implementation
    init_media_cmd_module(bot);

    bot.start(dpp::st_wait);

}

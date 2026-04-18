#include "media.hpp"

void init_media_cmd_module(dpp::cluster& bot) {

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {

        if (event.command.get_command_name() == "fih") {
            event.reply("https://cdn.discordapp.com/attachments/875395171880165398/879642028462448650/phishe.mp4");

        }

    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {

        if (event.command.get_command_name() == "fihgam") {
            event.reply("https://cdn.discordapp.com/attachments/1438382745226055885/1493145776006758441/its_fish.mp4?ex=69df395e&is=69dde7de&hm=e5221e9b45e23f6feba0dcb8fc8347f61071b3e366e4ceb95f115043c9c01ed9&");

        }

    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {

        if (event.command.get_command_name() == "doorknob") {
            event.reply("https://cdn.discordapp.com/attachments/529475315953696770/876700584227508234/caption.gif");

        }

    });

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {

        if (event.command.get_command_name() == "men") {
            event.reply("https://images-ext-2.discordapp.net/external/r1D3sXARLGLKXWiO6q8FSeRh42EOFXQkRSl_uSeW450/https/media.tenor.com/0UX3tOVLMKEAAAPo/kingmichel33-tik-tok.mp4");

        }

    });

}

#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H


enum MessageType{
    connection,     //when a player wants to connect to a server
    disconnection,  //when a player quits a game (server logout)
    startGame,      //send by the server to signal the begining of the game to everyone
    endGame,        //send by the server to signal the end of the game to everyone
    answer,         //to acknowledge receipt of a message
    sendMap,        //when the server sends the map to everyone
    newMap,         //when the host sends the map to the server
    sendEntity,     //when the message contain entity
    listPlayer,     //when the server sends the list of the players
    idPlayer,       //when the server accepts a connection he sends an id to the player
    gameWon,        //when the player reaches the end of the game and wins
};





#endif // MESSAGETYPE_H

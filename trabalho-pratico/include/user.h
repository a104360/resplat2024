#ifndef USER_H
#define USER_H
#include "../include/time.h" 
#include "../include/database.h"
#include <stdbool.h>
/**
 * @brief Represents a type alias for the Database named Users.
 */
typedef Database Users;

/**
 * @brief Represents a structure for storing user information.
 */
typedef struct user User;

/**
 * @brief Allocates memory for a User structure and returns a pointer to it.
 * @return Pointer to the created User.
 */
User *createUser();

/**
 * @brief Initializes a User structure.
 * @param user Pointer to the User structure to be initialized.
 */
void initUser(User *);

/**
 * @brief Correctly frees the memory allocated for a User structure.
 * @param user Pointer to the User structure to be destroyed.
 */
void destroyUser(User *);

/**
 * @brief Sets the ID in the User structure.
 * @param user Pointer to the User structure.
 * @param id Pointer to a string ID.
 */
void setUserId(User *, const char *);

/**
 * @brief Gets the ID stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the ID string.
 */
char *getUserId(User *);

/**
 * @brief Sets the user name in the User structure.
 * @param user Pointer to the User structure.
 * @param name Pointer to a string representing the user name.
 */
void setUserName(User *, const char *);

/**
 * @brief Gets the user name stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user name string.
 */
char *getUserName(User *);

/**
 * @brief Sets the user email in the User structure.
 * @param user Pointer to the User structure.
 * @param email Pointer to a string representing the user email.
 */
void setUserEmail(User *, const char *);

/**
 * @brief Gets the user email stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user email string.
 */
char *getUserEmail(User *);

/**
 * @brief Sets the user phone number in the User structure.
 * @param user Pointer to the User structure.
 * @param phone Pointer to a string representing the user phone number.
 */
void setUserPhone(User *, const char *);

/**
 * @brief Gets the user phone number stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user phone number string.
 */
char *getUserPhone(User *);

/**
 * @brief Sets the user birthday in the User structure.
 * @param user Pointer to the User structure.
 * @param bday Pointer to a Time struct representing the user birthday.
 */
void setUserBday(User *, Time *);

/**
 * @brief Gets the pointer to the user birthday stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user birthday.
 */
Time *getUserBday(User *);

/**
 * @brief Sets the user sex in the User structure.
 * @param user Pointer to the User structure.
 * @param sex Char representing the user sex.
 */
void setUserSex(User *, const char);

/**
 * @brief Gets the user sex stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Char representing the user sex.
 */
char getUserSex(User *);

/**
 * @brief Sets the user passport information in the User structure.
 * @param user Pointer to the User structure.
 * @param passport Pointer to a string representing the user passport.
 */
void setUserPassport(User *, const char *);

/**
 * @brief Gets the user passport information stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user passport string.
 */
char *getUserPassport(User *);

/**
 * @brief Sets the user country code in the User structure.
 * @param user Pointer to the User structure.
 * @param countryCode Pointer to a string representing the user country code.
 */
void setUserCountryCode(User *, const char *);

/**
 * @brief Gets the user country code stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user country code string.
 */
char *getUserCountryCode(User *);

/**
 * @brief Sets the user address in the User structure.
 * @param user Pointer to the User structure.
 * @param address Pointer to a string representing the user address.
 */
void setUserAddress(User *, const char *);

/**
 * @brief Gets the user address stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user address string.
 */
char *getUserAddress(User *);

/**
 * @brief Sets the user account creation time in the User structure.
 * @param user Pointer to the User structure.
 * @param accountCreation Pointer to a Time struct representing the user account creation time.
 */
void setUserAccountCreation(User *, Time *);

/**
 * @brief Gets the pointer to the user account creation time stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user account creation time.
 */
Time *getUserAccountCreation(User *);

/**
 * @brief Sets the user payment method in the User structure.
 * @param user Pointer to the User structure.
 * @param payMethod Pointer to a string representing the user payment method.
 */
void setUserPayMethod(User *, const char *);

/**
 * @brief Gets the user payment method stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Pointer to the user payment method string.
 */
char *getUserPayMethod(User *);

/**
 * @brief Sets the user account status in the User structure.
 * @param user Pointer to the User structure.
 * @param accountStatus Boolean value indicating the user account status.
 */
void setUserAccountStatus(User *, const bool);

/**
 * @brief Gets the user account status stored in the User structure.
 * @param user Pointer to the User structure.
 * @return Boolean value indicating the user account status.
 */
bool getUserAccountStatus(User *);

/**
 * @brief Gets the user age calculated from the user birthday.
 * @param user Pointer to the User structure.
 * @return User age.
 */
int getUserAge(User *);

/**
 * @brief Copies the contents of one User structure to another.
 * @param dest Pointer to the destination User structure.
 * @param src Pointer to the source User structure.
 */
void copyUser(User *, User *);


#endif
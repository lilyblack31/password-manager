### Compile using the following (in the src folder): 

``` g++ -std=c++11 -o password_manager main.cpp PasswordManager.cpp PasswordGenerator.cpp Encryption.cpp UserAuth.cpp utils.cpp -lssl -lcrypto ```

Need to specify the std=c++11 as it uses functionalities specific to that version. 

### After compiling, run the binary file:

``` ./password_manager ```

### Need to do in the future: 

- Have separate users login page
- ask the masterkey everytime an action is performed (after login)
- Make the view password not based on username 
- Ability to see all the passwords stored under a specific login (after inputting the master key)
- expand to GUI using Qt (?)
- Password masking (additional layer of security)
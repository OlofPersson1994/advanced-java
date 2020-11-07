package com.creativeTtech;
import java.util.*;
public class controller {

    String inputPassword;
    String password = "password";
    String welcomeText = "Welcome to passwordKeeper\nPlease put in your masterpassword.";
    String option = ("1: Login\n2: Add new password");
    int wrongMasterPasswordCounter = 3;
    boolean loggedOut = true;


    public controller() {

        passwordContainer passwordContainer = new passwordContainer();
        System.out.println(welcomeText);

        while (loggedOut) {

            Scanner masterPasswordScanner = new Scanner(System.in);
            String masterPasswordInput = masterPasswordScanner.nextLine();

            if (password.equals(masterPasswordInput)) {
                System.out.println("You are logged in.");
                loggedOut = false;
            }

            else if (wrongMasterPasswordCounter == 0){
                System.out.println("Sorry your have put in the wrong masterpassword to many times, all your password will now be deleted.");
            }

            else if (wrongMasterPasswordCounter != 0) {
                System.out.println("Wrong masterpassword, please try again. You have " + wrongMasterPasswordCounter + " attemts left.");
                wrongMasterPasswordCounter--;
            }

        }


        while (true) {

            System.out.println(option);
            Scanner menyScanner = new Scanner(System.in);
            int menyInput = menyScanner.nextInt();


            if (menyInput == 1) {

                System.out.println("Printing the list with passwords: \n");

               passwordContainer.printList(passwordContainer.list);

            }
            if (menyInput == 2) {

                System.out.println("Put in the new password:");

                menyScanner = new Scanner(System.in);
                password = menyScanner.nextLine();

                System.out.println("The new password is: " + password);
            }
        }
    }
}


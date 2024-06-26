# Technologies Used

<b>C++ | Qt | CMake</b>

# Dogs Adoption App

<b>The app can be used in two modes:</b>

-   User Mode
-   Administrator Mode

<b>When the application is started, it will offer the option to select the mode.</b>

### Administrator mode

> The application will have a database that holds all the dogs in the shelter at a given moment. The admin can:
> - add a new dog
> - delete a dog (when the dog is adopted)
> - update the information of a dog

> Each Dog has a breed, a name, an age and a photograph. The photograph is memorised as a link towards an online resource (the photograph on the presentation site of the centre). The administrators will also have the option to see all the dogs in the shelter.

### User mode

> A user can access the application and choose one or more dogs to adopt. The user can:
> - See the dogs in the database, one by one. When the user chooses this option, the data of the first dog (breed, name, age) is displayed, along with its photograph.
> - Choose to adopt the dog, in which case the dog is added to the user’s adoption list.
> - Choose not to adopt the dog and to continue to the next. In this case, the information corresponding to the next dog is shown and the user is again offered the possibility to adopt it. This can continue as long as the user wants, as when arriving to the end of the list, if the user chooses next, the application will again show the first dog.
> - See all the dogs of a given breed, having an age less than a given number. If no breed is provided, then all the dogs will be considered. The functionalities outlined above apply again in this case.
> - See the adoption list.
> - undo / redo the last performed operation
---

    @neon1024

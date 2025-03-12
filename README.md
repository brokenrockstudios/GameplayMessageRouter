# GameplayMessageRouter
A community plugin version of GameplayMessage Processor from the Epic's Lyra Sample project

The GameplayMessageRouter acts as a centralized hub for routing, processing, and dispatching gameplay
messages. It decouples message senders from listeners, making your game's event communication more
modular, scalable, and easier to maintain

## 📖 Overview

The GameplayMessageRouter is designed to streamline communication between disparate gameplay components by:
 * Centralizing message routing
   * All gameplay messages, events, state changes, or notifications are managed by a single router
 * Decoupling components
   * Senders and receivers don't need direct references to each other, reducing dependencies and simplifying maintenance
 * Supporting both C++ and Blueprints.
   * Can easily integrate into any combination of language

By using this system, you can easily add/remove, or update interactions between separate game systems without
modifying each individual module. 

## 🛠️ Usage


### Blueprints
TODO pictures


### C++

Broadcast a message
```cpp
FYourStructMessage Message;
// Message.SomeValue = SomeOtherValue;
...populate message

UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(this);
MessageSystem.BroadcastMessage(SomeGameplayTag, Message);
```

Register a listener
```cpp
UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
FGameplayMessageListenerHandle ListenerHandle =MessageSubsystem.RegisterListener(SomeGameplayTag, this, &ThisClass::OnSomeMessage);
...
void YourClass::OnSomeMessage(FGameplayTag Channel, const FYourStructMessage& Payload) {}
```

Unregister a listener
```cpp
UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
MessageSubsystem.UnregisterListener(ListenerHandle);
```


## 📦 Installation

1. Download or clone and place in your `Plugins` folder.
2. For C++ projects, add the following line to your `YourProject.Build.cs` file:
```csharp
PublicDependencyModuleNames.AddRange(new string[] { "GameplayMessageRuntime" });
```
Rebuild the project

### From Lyra

Remove the old plugin and GameplayMessageProcessor.h/.cpp

# 📃 License
This project is a fork of Epic Games' codebase and is therefor subject to the Unreal Engine EULA and the Unreal Engine Content EULA.
Any portions of the code that are not covered by Epic's EULA are licensed under the MIT License, as specified in the LICENSE file.


# 🔄Notable changes from original
(Not an exhaustive list)

* Added GameplayMessageProcessor

# 🔗 Relevant Links

* Lyra Sample Project Documentation: https://dev.epicgames.com/documentation/en-us/unreal-engine/lyra-sample-game-in-unreal-engine
* Download Lyra Sample Project: https://www.fab.com/listings/93faede1-4434-47c0-85f1-bf27c0820ad0 

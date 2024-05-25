# Dice/CharacterBase
 
## CharacterBase.h
 * CharacterPlayer, NonPlayerCharacter의 부모 클래스로 동작한다.
   
 * 카메라의 지지대 역할을 하는 SpringArmComponent와 카메라의 역할을 하는 CameraComponent로 구성되어있다.
   
 * 캐릭터의 최대 HP를 설정하는 Getter, Setter 함수 SetMaxHp(), GetMaxHp()가 있다.

 * 캐릭터의 현재 HP를 설정하는 Getter, Setter 함수 SetCurrentHp(), GetCurrentHp()가 있다.

 * 캐릭터의 현재 생존여부를 판단하는 IsDead() 함수가 있다.

 * 해당 클래스를 상속하여 새로운 캐릭터를 만들고 싶다면 .h 파일에 #include "Character/CharacterBase.h"를 추가한다.
   
## CharacterBase.cpp

## CharacterPlayer.h

## CharacterPlayer.cpp

## NonPlayerCharacter.h

## NonPlayerCharacter.cpp

## DefaultEngine.ini



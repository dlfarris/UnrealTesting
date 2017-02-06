// Just doing Tutorial Stuff

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is Here!"));

	PlayerController = GetWorld()->GetFirstPlayerController();


	/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandle Component"), *(GetOwner()->GetName()));
	}

	/// Look for Input Handler
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found"));
		/// Bind the input axis
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab()
{
	/// Get Player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// Draw a red trace in the world to visualize
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0, 10.f);

	/// setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Raycast to certain distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	if (Hit.Actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *(Hit.Actor->GetName()));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Key Released"));
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );



	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	

	// see what we hit
}


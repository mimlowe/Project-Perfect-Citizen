#include "UpdateCmpntDecorator.h"

using namespace ppc;

updateCmpntDecorator::updateCmpntDecorator(
	UpdateComponent& updatePtr): uCmpntHandle_(&updatePtr){}

updateCmpntDecorator::~updateCmpntDecorator() {
	delete uCmpntHandle_;
}

Entity* updateCmpntDecorator::getEntity() {
	return uCmpntHandle_->getEntity();
}

void updateCmpntDecorator::recieveMessage(msgType message) {
	uCmpntHandle_->recieveMessage(message);
}

void updateCmpntDecorator::update(sf::Time& deltaTime) {
	uCmpntHandle_->update(deltaTime);
}
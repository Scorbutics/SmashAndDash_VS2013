#include "SpreadingTextureParticleEffectFactory.h"
#include "SpreadingParticleEffectFactory.h"
#include "TextureGraphicParticleRenderer.h"
#include "SpritePathProperty.h"
#include "TextureAlphaParticleUpdater.h"


std::unique_ptr<ska::ParticleEffect> ska::SpreadingTextureParticleEffectFactory::createEffect(SDLRenderer& renderer, const SpreadingParticleSystemData & data) {
	auto particleSystem = SpreadingParticleEffectFactory::createEffect(renderer, data);
	particleSystem->applyGroupProperty<SpritePathProperty>(data.spritePath);
	particleSystem->addUpdater<TextureAlphaParticleUpdater>(data.lifetime);
	particleSystem->addRenderer<TextureGraphicParticleRenderer>();
	return std::move(particleSystem);
}

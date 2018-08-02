//  Created by Theo Penavaire on 06/03/2018
//  Last Update on 06/07/2018 

#pragma once

#include "neon_engine.h"
#include "Core.h"

namespace neon_engine
{

	/**
	 * \brief Base class for every object managed by the graphical library (SDL2)
	 */
	class IUIObject
	{

	public:
		virtual			~IUIObject() = default;

		/**
		 * \brief Update state of the game object relatively to events
		 * \param event Data for event that just occured
		 */
		virtual void	update(NEvent& event) = 0;
		
		/**
		 * \brief Draw the game object on screen
		 * \param renderer Renderer's instance
		 */
		virtual void	draw(RendererSptr& renderer) = 0;

		/**
		 * \brief Setter for the hasFocus variable. hasFocus must be set to true
		 * if the game object is currently selected by user.
		 * \param hasFocus true if the game object has focus.
		 */
		virtual void	setHasFocus(bool hasFocus) = 0;

		/**
		 * \brief Getter for hasFocus
		 * \return true if the game object has focus
		 */
		virtual bool	getHasFocus() const = 0;
		
		/**
		* \brief Enable rendering and interaction for the game object
		* \param e boolean
		*/
		virtual void	setIsEnabled(const bool e) = 0;

		/**
		* \brief Getter for the position
		* \return Position of the game object
		*/
		virtual Vector2<int>	getPos() const = 0;
		
		/**
		* \brief Setter for the position
		* \param pos New position of the game object
		*/
		virtual void			setPos(const Vector2<int> pos) = 0;

		/**
		* \brief Getter for the size
		* \return Size of the game object
		*/
		virtual Vector2<int>	getSize() const = 0;

		/**
		* \brief Setter for the size
		* \param size New size of the game object
		*/
		virtual void			setSize(const Vector2<int> size) = 0;
	};

}
#pragma once

#include "priority_queue_sorted_array_list.h"
#include <stdexcept>

namespace structures
{
    /// <summary> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
    template<typename T>
    class PriorityQueueLimitedSortedArrayList : public PriorityQueueSortedArrayList<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        PriorityQueueLimitedSortedArrayList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou, z ktoreho sa prevezmu vlastnosti. </param>
        PriorityQueueLimitedSortedArrayList(PriorityQueueLimitedSortedArrayList<T>& other);

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou. </summary>
        /// <param name = "priority"> Priorita vkladaneho prvku. </param>
        /// <param name = "data"> Vkladany prvok. </param>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front plny. </exception>
        void push(int priority, const T& data) override;

        /// <summary>
        ///  Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou.
        ///  V pripade, ze je prioritny front plny, odstrani polozku s najmensou prioritou z prioritneho frontu a vrati smernik na nu.
        ///  V opacnom pripade vrati nullptr.
        /// </summary>
        /// <param name = "priority"> Priorita vkladaneho prvku. </param>
        /// <param name = "data"> Vkladany prvok. </param>
        /// <returns> Smernik na odstranenu polozku alebo nullptr. </returns>
        PriorityQueueItem<T>* pushAndRemove(int priority, T data);

        /// <summary> Vrati najmensiu prioritu nachadzajucu sa v prioritnom fronte. </summary>
        /// <returns> Najmensiu priorita nachadzajuca sa v prioritnom fronte. </returns>
        int minPriority();

        /// <summary>
        ///  Pokusi sa zmenit kapacitu prioritneho frontu.
        ///  Kapacitu je mozne zmensit len ak nova kapacita nie je mensia ako aktualny pocet poloziek v prioritnom fronte.
        ///  V opacnom pripade nedojde k zmene kapacity.
        /// </summary>
        /// <param name = "capacity"> Nova kapacita. </param>
        /// <returns> true, ak sa kapacitu podarilo zmenit, false inak. </returns>
        bool trySetCapacity(size_t capacity);

    private:
        /// <summary> Kapacita prioritneho frontu. </summary>
        size_t capacity_;
    };

    template<typename T>
    PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList() :
        PriorityQueueSortedArrayList<T>(),
        capacity_(2)
    {
    }

    template<typename T>
    PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList(PriorityQueueLimitedSortedArrayList<T>& other) :
        PriorityQueueSortedArrayList<T>(other),
        capacity_(other.capacity_)
    {
    }

    template<typename T>
    inline Structure& PriorityQueueLimitedSortedArrayList<T>::assign(Structure& other)
    {
        if (this != &other) {
            PriorityQueueLimitedSortedArrayList<T>& otherPriorityQueueLimitedSortedArrayList =
                dynamic_cast<PriorityQueueLimitedSortedArrayList<T>&>(other);
            PriorityQueueSortedArrayList<T>::assign(otherPriorityQueueLimitedSortedArrayList);
            capacity_ = otherPriorityQueueLimitedSortedArrayList.capacity_;
        }
        return *this;
    }

    template<typename T>
    void PriorityQueueLimitedSortedArrayList<T>::push(int priority, const T& data)
    {
        if (PriorityQueueList<T>::list_->size() <= capacity_) {
            PriorityQueueSortedArrayList<T>::push(priority, data);
        }
        else {
            throw std::logic_error("PriorityQueueLimitedSortedArrayList push() capacity extends" + std::to_string(capacity_) + std::to_string(PriorityQueueList<T>::list_->size()));
        }


    }

    template<typename T>
    inline PriorityQueueItem<T>* PriorityQueueLimitedSortedArrayList<T>::pushAndRemove(int priority, T data)
    {
        if (capacity_ > PriorityQueueList<T>::list_->size()) {
  
            push(priority, data);
            return nullptr;
        }
        else {
            if (priority < PriorityQueueList<T>::list_->at(0)->getPriority()) {
                auto item = PriorityQueueList<T>::list_->removeAt(0);
                push(priority, data);
                return item;
            }
            else {
                return new PriorityQueueItem<T>(priority, data);
            }
        }

    }

    template<typename T>
    inline int PriorityQueueLimitedSortedArrayList<T>::minPriority()
    {
        if (!(PriorityQueueSortedArrayList<T>::list_->size()>0)) {
            throw std::logic_error("PriorityQueueLimitedSortedArrayList minPriority() size is 0)!");
        }
        return PriorityQueueSortedArrayList<T>::list_->at(0)->getPriority();
    
    }

    template<typename T>
    inline bool PriorityQueueLimitedSortedArrayList<T>::trySetCapacity(size_t capacity)
    {
        if(PriorityQueueSortedArrayList<T>::list_->size()< capacity){
            capacity_ = capacity;
                return true;
        }
        return false;
    }
}
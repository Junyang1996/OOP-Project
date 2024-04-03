#include <fstream>
#include <iostream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
namespace seneca
{
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        try
        { // open the file
            std::fstream fs(file);
            // loop for each line
            // size_t i = 0u;

            Utilities util;

            util.setDelimiter('|');
            std::string line{};
            // store the workstation as the prior as the current workstation and the later as nextworkstation
            while (std::getline(fs, line))
            {
                size_t pos = 0;
                bool more = false;

                // m_activeLine[i] = new Workstation(util.extractToken(line, pos, more));
                // m_activeLine[i]->setNextStation(util.extractToken(line, pos, more));
                std::string firstObject = util.extractToken(line, pos, more);
                auto currentStation = std::find_if(stations.begin(), stations.end(),
                                                   [&](Workstation *station)
                                                   { return station->getItemName() == firstObject; });

                if (more)
                {
                    std::string secondObject = util.extractToken(line, pos, more);
                    auto nextStation = std::find_if(stations.begin(), stations.end(),
                                                    [&](Workstation *station)
                                                    { return station->getItemName() == secondObject; });
                    if (currentStation != stations.end() && nextStation != stations.end())
                    {
                        m_activeLine.push_back(*currentStation);
                        (*currentStation)->setNextStation(*nextStation);
                    }
                }
                else
                {
                    m_activeLine.push_back(*currentStation);
                }
            }
            // once it's all done, if there's a workstation has no been in any next workstation, it is the first workstation
            auto firstStation = std::find_if_not(m_activeLine.begin(), m_activeLine.end(), [&stations](Workstation *ws)
                                                 { return std::any_of(stations.begin(), stations.end(), [ws](Workstation *other)
                                                                      { return other->getNextStation() == ws; }); });
            m_firstStation = *firstStation;
            // count the total orders in each of the stations.
            // auto totalOrder = std::accumulate(m_activeLine.begin(), m_activeLine.end(), 0, [](int sum, const Workstation *ws)
            //                                   { return sum + ws. })
            m_cntCustomerOrder = g_pending.size();
        }
        catch (const char *)
        {
            throw;
        }
        catch (std::out_of_range)
        {
            throw;
        }
        catch (...)
        {
            throw;
        }
    }
    void LineManager::reorderStations()
    {
        std::vector<Workstation *> reordered;
        Workstation *currentStation = m_firstStation;
        while (currentStation != nullptr)
        {
            reordered.push_back(currentStation);
            currentStation = currentStation->getNextStation();
        }
        m_activeLine = reordered;
    }
    bool LineManager::run(std::ostream &os)
    {
        *m_firstStation += std::move(g_pending.front());
        auto i = 0u;
        while (m_activeLine[i]->attemptToMoveOrder())

        {
            os << "Line Manager Iteration: " << i + 1 << std::endl;

            m_activeLine[i]->fill(os);
            m_activeLine[i]->attemptToMoveOrder();
        }

        return true;
    }
    void LineManager::display(std::ostream &os) const
    {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *ws)
                      { ws->display(os); });
    }
}

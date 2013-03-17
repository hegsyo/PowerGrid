TODO-list
=========

Below are the most direct TODO-items and their requirements. They are placed in 
order of importance, so it is advised to take on the top most action item that is 
not claimed by anyone (using [NAME]). [DONE] can be placed in front of achieved 
subgoals to indicate progress.

+--------Thoughts Box (Add stuff that you want to discuss here)----------------+
| <none>                                                                       |
+------------------------------------------------------------------------------+

- Household work (I know: boring, but it has to happen, too)
    1. [Chronio] (Re-)write documentation
        10. [BUSY] check / update Javadoc to match latest changes / features
        11. [SKIP] update the class tree file with info on all classes
        12. [DONE] check / update README.md file.

- Enable dynamic Lodestone checking
    1. Enable when PathFinding and Lodestones are not yet checked.
    2. Assuming unlocked Lodestones do not change, do not recheck for each computed path.
    3. Read from cache when Lodestones have been checked already.

- Create working interactions
    1. Door
    2. Gate

- Make 'TravelToNearest' command and test it
    1. Method always travels to nearest destination (including Teleports)
    2. Method allows for filter of params (specific ore type, for example) and choose destination accordingly
    3. Method is location independant (involves having specialLocation data in environment)

- Gadgets, Details, Cool stuff and more...
    1. Have a 'thoughts' balloon for PowerWalk, allowing the end-user to 'peek' into PowerWalk's decisions.
        10. This allows for ad-hoc decision-making without end-users going nuts due to PowerWalk doing 'weird' things.
        11. It's easier to debug tasks when you know what PowerWalk's up to.
        12. It would provide the idea that PowerWalk works as an actual player and therefore enhance the awesomeness of PowerWalk.
    2. Add (more) cool and would-be-awesome ideas to this list.
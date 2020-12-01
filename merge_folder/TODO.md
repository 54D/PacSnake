# TODO List
As a self-reminder

## Add Out-of bound Checking Condition
~~No info for num_row and num_col at the moment~~
- [ ] ~~Entity::set_row()~~
- [ ] ~~Entity::set_col()~~
- [ ] ~~Entity::set_coordinate()~~
- [ ] ~~Entity::set_relative_coordinate()~~

Need to be done outside as num_row and num_col are data member of game_map

## Review Permission of Member Function
public, protected, private, friend

## Snake speed
- [ ] Snake::calculate_level_speed()
- [ ] PU_Dash::activate()

## Power Up

### Number of Power Up Activate At the Same Time
- [ ] Disalbe activate option is there is already an power up activating
- Currently set to 1 only 

### Constructor destructor
- When to call to delete the power up on map?
    - Constructor and destructor
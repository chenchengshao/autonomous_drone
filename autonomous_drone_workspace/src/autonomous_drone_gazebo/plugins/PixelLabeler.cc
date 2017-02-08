/* =============================================================================
 * Name  : PixelLabeler.cc
 * Author: David Justo
 * Email : david.justo.1996@gmail.com
 * Description : Implementation of the PixelLabeler plugin for the autonomous
 *               flying prone project. More details on the class description.
 * ===========================================================================*/

#include <gazebo/math/Rand.hh>            //TODO: is this necessary?
#include <gazebo/gui/GuiIface.hh>
#include <gazebo/rendering/rendering.hh>
#include <gazebo/gazebo.hh>
#include <gazebo/math/Vector2i.hh>

namespace gazebo
{

  /* ---------------------------------------------------------------------------
   * ClassName: PixelLabeler
   * Description : A Gazebo system plugin that outputs an vector or entity IDs
   *               for each pixel on a given camera
   * ------------------------------------------------------------------------ */
  class SystemGUI : public SystemPlugin
  {

  // ========================= VARIABLE DECLARATIONS ===========================

  private: rendering::UserCameraPtr userCam; // pointer to the userCamera TODO
  private: std::vector<event::ConnectionPtr> connections;  // rendering events

  // ========================= FUNCTION DECLARATIONS ===========================

  /*----------------------------------------------------------------------------
   * Function name : ~SystemGUI (Destructor)
   * Purpose : To release all memory and exit cleanly. Release ownership of
   *           the userCamera sharedPtr and clears the vector of OGRE/GAZEBO
   *           rendering event connections.
   * ------------------------------------------------------------------------ */
  public: virtual ~SystemGUI()
  {
    this->connections.clear();
    if (this->userCam)
      this->userCam->EnableSaveFrame(false);
    this->userCam.reset();
  }

  /*----------------------------------------------------------------------------
   * Function name : ~SystemGUI (Destructor)
   * Purpose : To release all memory and exit cleanly. Release ownership of
   *           the userCamera sharedPtr and clears the vector of OGRE/GAZEBO
   *           rendering event connections. Called ONCE after constructor.
   * ------------------------------------------------------------------------ */
  public: void Load(int /*_argc*/, char ** /*_argv*/)
  {
    this->connections.push_back(
      event::Events::ConnectPreRender(
        boost::bind(&SystemGUI::Update, this)));
  }

  // Init: Called once after Load. Trivial for our purposes
  private: void Init(){}

  /*----------------------------------------------------------------------------
   * Function name : Update
   * Purpose : Called before EVERY PreRender event (consult Load function).
   *           [TODO: COMPLETE ME]
   * ------------------------------------------------------------------------ */
  private: void Update()
  {


    if (!this->userCam)
    {
      // Get a pointer to the active user camera
      this->userCam = gui::get_active_camera();

      // Enable saving frames
      this->userCam->EnableSaveFrame(true);

      // Specify the path to save frames into
      this->userCam->SetSaveFramePathname("/tmp/gazebo_frames");
    }

    // Get scene pointer
    rendering::ScenePtr scene = rendering::get_scene();

    // Wait until the scene is initialized.
    if (!scene || !scene->GetInitialized())
    return;

    // Look for a specific visual by name.
    if (scene->GetVisual("ground_plane"))
    std::cout << "Has ground plane visual\n";

    unsigned int vw = this->userCam->GetViewportWidth();
    unsigned int vh = this->userCam->GetViewportHeight();

    for (int i = 0; i < vw; ++i)
    {
      for (int j = 0; j < vh; ++j)
      {
      	math::Vector2i vec = math::Vector2i(i,j);
      	rendering::VisualPtr temp = scene->GetVisualAt(this->userCam, vec);
      	if(temp){
      		auto id = temp->GetName();
      	  std::cout << id << "\n";
        }
      }
    }
  }

  /*
  private: void LabelPixels()
  {

    // [TODO: Find a faster method. Vectorization, maybe?]

    for(int col = 0; col < vwidth; col++)
    {
      for(int row = 0; row < vheight; row++)
      {

        // Establish the pixel position and extract the entity at that position
        math::Vector2i pos = math::Vector2i(col,row);
        rendering::VisualPtr entity = scene->GetVisualAt(this->userCam, pos);

        // If there exists an entity at that position...
        if(entity)
        {
          // [TODO: Determine how to output this data]
          auto id = temp->GetName();
          std::cout << id << "\n";
        }
      }
      } */
    };

  // Register this plugin with Gazebo
  GZ_REGISTER_SYSTEM_PLUGIN(SystemGUI)
}
